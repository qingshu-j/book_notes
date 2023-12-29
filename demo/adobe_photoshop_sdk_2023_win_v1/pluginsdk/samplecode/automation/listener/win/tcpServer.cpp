
#include "mongoose.h"
#include <string>

static const char *s_lsn = "tcp://localhost:8765";   // Listening address

void mycopy();

// SERVER event handler
static void sfn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
	if (ev == MG_EV_OPEN && c->is_listening == 1) {
		MG_INFO(("SERVER is listening"));
	}
	else if (ev == MG_EV_ACCEPT) {
		MG_INFO(("SERVER accepted a connection"));
#if MG_ENABLE_MBEDTLS || MG_ENABLE_OPENSSL
		struct mg_tls_opts opts = {
			//.ca = "ss_ca.pem",         // Uncomment to enable two-way SSL
			.cert = "ss_server.pem",     // Certificate PEM file
			.certkey = "ss_server.pem",  // This pem contains both cert and key
		};
		mg_tls_init(c, &opts);
		MG_INFO(("SERVER initialized TLS"));
#endif
	}
	else if (ev == MG_EV_READ) {
		struct mg_iobuf *r = &c->recv;
		MG_INFO(("SERVER got data: %.*s", r->len, r->buf));
		std::string strRecv;
		strRecv.assign((const char*)r->buf, r->len);
		if (strRecv.find("copy")!=-1)
		{
			mycopy();
		}
		mg_send(c, r->buf, r->len);  // echo it back
		r->len = 0;                  // Tell Mongoose we've consumed data
	}
	else if (ev == MG_EV_CLOSE) {
		MG_INFO(("SERVER disconnected"));
	}
	else if (ev == MG_EV_ERROR) {
		MG_INFO(("SERVER error: %s", (char *)ev_data));
	}
	(void)fn_data;
}


//// SERVER event handler
//static void sfn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
//	if (ev == MG_EV_OPEN && c->is_listening == 1) {
//		MG_INFO(("SERVER is listening"));
//	}
//	else if (ev == MG_EV_ACCEPT) {
//		MG_INFO(("SERVER accepted a connection"));
//		//if (mg_url_is_ssl(s_lsn)) {
//		//	struct mg_tls_opts opts = { .ca = mg_unpacked("/certs/ss_ca.pem"),
//		//		.cert = mg_unpacked("/certs/ss_server.pem"),
//		//		.key = mg_unpacked("/certs/ss_server.pem") };
//		//	mg_tls_init(c, &opts);
//		//}
//	}
//	else if (ev == MG_EV_READ) {
//		struct mg_iobuf *r = &c->recv;
//		MG_INFO(("SERVER got data: %.*s", r->len, r->buf));
//		std::string strRecv;
//		strRecv.assign((const char*)r->buf, r->len);
//		if (strRecv=="copy")
//		{
//			mycopy();
//		}
//		mg_send(c, r->buf, r->len);  // echo it back
//		r->len = 0;                  // Tell Mongoose we've consumed data
//	}
//	else if (ev == MG_EV_CLOSE) {
//		MG_INFO(("SERVER disconnected"));
//	}
//	else if (ev == MG_EV_ERROR) {
//		MG_INFO(("SERVER error: %s", (char *)ev_data));
//	}
//	(void)fn_data;
//}


#ifdef _WIN32

#include <windows.h>

bool g_ThreadRun = true;

DWORD WINAPI ThreadFunc(LPVOID lpThreadParameter);


void MyShutdown(void)
{
	g_ThreadRun = false;
}


void MyStartup(void)
{
	g_ThreadRun = true;
	DWORD threadId = 0;
	HANDLE workThreadHandle = CreateThread(NULL, 0, ThreadFunc, NULL, 0, &threadId);
	CloseHandle(workThreadHandle);
}

DWORD WINAPI ThreadFunc(LPVOID lpThreadParameter)
{
	struct mg_mgr mgr;  // Event manager
	struct mg_connection *c;

	mg_log_set(MG_LL_VERBOSE);  // Set log level
	mg_mgr_init(&mgr);       // Initialize event manager

	c = mg_listen(&mgr, s_lsn, sfn, NULL);  // Create server connection
	if (c == NULL) {
		MG_INFO(("SERVER cant' open a connection"));
		return 0;
	}
	while (g_ThreadRun)
		mg_mgr_poll(&mgr, 1000);  // Infinite event loop, blocks for upto 100ms
								 // unless there is network activity
	mg_mgr_free(&mgr);         // Free resources
	return 0;
}


#endif