using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Timers;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;
using System.Net.Sockets;
using System.Runtime.InteropServices;

using Microsoft.Research.Kinect.Nui;

namespace KinectDaemon
{
	[StructLayout(LayoutKind.Sequential, Pack=1)]
	public struct PacketK
	{
		public int x;
		public int z;
	}
	
	public partial class MainWindow : Window
	{
		Runtime runtime = null;
		DispatcherTimer timer = null;
		UdpClient client = null;
		int lastTrackingIndex = -1;
		
		public MainWindow()
		{
			InitializeComponent();
			
			runtime = new Runtime();
		}
		
		static byte[] StructureToByteArray(object obj)
		{
			int len = Marshal.SizeOf(obj);
			byte[] array = new byte[len];
			
			IntPtr ptr = Marshal.AllocHGlobal(len);
			Marshal.StructureToPtr(obj, ptr, true);
			Marshal.Copy(ptr, array, 0, len);
			Marshal.FreeHGlobal(ptr);
			
			return array;
		}
		
		public static void result(IAsyncResult ar)
		{
			
		}
		
		void timer_Tick(object sender, EventArgs e)
		{
			SkeletonFrame frame = runtime.SkeletonEngine.GetNextFrame(0);
			
			if (frame == null)
				return;
			
			foreach (SkeletonData skeleton in frame.Skeletons)
			{
				if (skeleton.TrackingState == SkeletonTrackingState.Tracked)
				{
					// filter out people in the background
					if (lastTrackingIndex == -1)
					{
						lastTrackingIndex = skeleton.TrackingID;
					}
					else if (skeleton.TrackingID != lastTrackingIndex)
					{
						continue;
					}
					
					Joint head = skeleton.Joints[JointID.Head];
					
					if (head.TrackingState != JointTrackingState.Tracked)
						return;
					
					float posX = head.Position.X;
					int posXScaled = (int) (posX * 200);
					int posZScaled = (int) (head.Position.Z * 100);
					
					canvas1.Children.Clear();
					
					Color circleColor = Colors.Green;
					
					if (posZScaled > 140)
					{
						circleColor = Colors.Red;
					}
					else if (posZScaled < 120)
					{
						circleColor = Colors.Blue;
					}
					
					Ellipse ellipse = new Ellipse();
					ellipse.Width = ellipse.Height = 64;
					ellipse.Fill = new SolidColorBrush(circleColor);
					
					Canvas.SetLeft(ellipse, 289 - 32 + posXScaled);
					canvas1.Children.Add(ellipse);
					
					PacketK packet = new PacketK()
					{
						x = posXScaled,
						z = posZScaled
					};
					
					byte[] bytes = StructureToByteArray(packet);
					client.BeginSend(bytes, bytes.Length, new AsyncCallback(result), null);
					
					return;
				}
			}
		}
		
		private void Window_Loaded(object sender, RoutedEventArgs e)
		{
			runtime.Initialize(RuntimeOptions.UseSkeletalTracking);
			runtime.SkeletonEngine.TransformSmooth = true;
			
			client = new UdpClient();
			client.Connect("localhost", 2338);
			
			timer = new DispatcherTimer();
			timer.Interval = TimeSpan.FromMilliseconds(1000 / 10); // 1/10 of a second
			timer.Tick += new EventHandler(timer_Tick);
			timer.Start();
		}
		
		private void Window_Closed(object sender, EventArgs e)
		{
			runtime.Uninitialize();
		}
	}
}
