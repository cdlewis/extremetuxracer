#include "kinect.h"

#define PORT 2338

int net_thread(void *param);

CKinect::CKinect() {
	m_quit = false;
	m_thread = NULL;
	m_axisMutex = SDL_CreateMutex();
}

bool CKinect::StartServer() {
	if (SDLNet_Init() == -1) {
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		return false;
	}
	
	m_connection = SDLNet_UDP_Open(PORT);
	
	if (!m_connection) {
		fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		return false;
	}
	
	m_packet = SDLNet_AllocPacket(512);
	
	if (!m_packet) {
		SDLNet_UDP_Close(m_connection);
		m_connection = NULL;
		
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		return false;
	}
	
	m_thread = SDL_CreateThread(&net_thread, this);
	
	if (m_thread == NULL) {
		fprintf(stderr, "Unable to create thread: %s\n", SDL_GetError());
		return false;
	}
	
	return true;
}

void CKinect::StopServer() {
	m_quit = true;
	
	if (m_thread) {
		SDL_WaitThread(m_thread, NULL);
	}
	
	SetAxis(0.0f, 0.0f);
	
	if (m_connection) {
		SDLNet_UDP_Close(m_connection);
		m_connection = NULL;
	}
	
	if (m_packet) {
		SDLNet_FreePacket(m_packet);
		m_packet = NULL;
	}
	
	SDLNet_Quit();
}

float CKinect::GetXAxis() {
	float tmp = 0.0f;
	
	SDL_mutexP(m_axisMutex);
	tmp = m_xaxis;
	SDL_mutexV(m_axisMutex);
	
	return tmp;
}

float CKinect::GetZAxis() {
	float tmp = 0.0f;
	
	SDL_mutexP(m_axisMutex);
	tmp = m_zaxis;
	SDL_mutexV(m_axisMutex);
	
	return tmp;
}

void CKinect::SetAxis(float x, float z) {
	SDL_mutexP(m_axisMutex);
	m_xaxis = x;
	m_zaxis = z;
	
	SDL_Event user_event;
	user_event.type=SDL_USEREVENT;
	user_event.user.code=KINECT_EVENT;
	user_event.user.data1=&m_xaxis;
	user_event.user.data2=&m_zaxis;
	
	SDL_PushEvent(&user_event);
	
	SDL_mutexV(m_axisMutex);
}

int net_thread(void *param) {
	CKinect *k = (CKinect *) param;
	
	while (!k->m_quit) {
		if (SDLNet_UDP_Recv(k->m_connection, k->m_packet)) {
			int *data_stream = (int *) k->m_packet->data;
			
			int val = data_stream[0];
			int val2 = data_stream[1];
			
			k->SetAxis(val / 100.0f, val2 / 100.0f);
		}
	}
	
	return 0;
}

CKinect::~CKinect() {
	SDL_DestroyMutex(m_axisMutex);
}
