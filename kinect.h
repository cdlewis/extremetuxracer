#ifndef KINECT_H
#define KINECT_H

#include "SDL/SDL_net.h"
#include "SDL/SDL_thread.h"

#define KINECT_EVENT 3259

class CKinect {
private:
	float m_xaxis, m_zaxis;
	SDL_mutex *m_axisMutex;
	SDL_Thread *m_thread;
public:
	UDPsocket m_connection;
	UDPpacket *m_packet;
	bool m_quit;
	
	CKinect();
	~CKinect();
	
	bool StartServer();
	void StopServer();
	
	float GetXAxis();
	float GetZAxis();
	void SetAxis(float x, float z);
};

#endif
