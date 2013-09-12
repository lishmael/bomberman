#include "WebClient.h"


WebClient::WebClient(DirectionSolver* ds) : solver(ds)   {
	if (solver == nullptr) {
		throw new std::invalid_argument("Solver cant be uninitialised!");
	}
}

void WebClient::run(std::string server, std::string user) {
	serverName = server;
	userName = user;
	std::string connectionString = serverName + "?user=" + userName;
	client.clear_access_channels(websocketpp::log::alevel::all);
	client.clear_error_channels(websocketpp::log::elevel::all);

	client.init_asio();
	client.set_message_handler(bind(&WebClient::onMessage, this, &client, ::_1, ::_2));
	websocketpp::lib::error_code err;
	Client::connection_ptr con = client.get_connection(connectionString, err);
	client.connect(con);
	client.run();
}

String WebClient::get() {
	return L"";
}

void WebClient::onMessage(Client* c, websocketpp::connection_hdl hdl, message_ptr pMsg) {
	Client::connection_ptr con = c->get_con_from_hdl(hdl);
	std::string res_s = con->get_resource();
	if (res_s != "/codenjoy-contest/ws?user=" + userName) {
		return;
	}
	std::string buffer_got = pMsg->get_payload();
	std::wstring boardString;
	boardString.resize(MultiByteToWideChar(CP_UTF8, 0, &buffer_got[0], buffer_got.length(),
													   NULL, 0));
	MultiByteToWideChar(CP_UTF8, 0, &buffer_got[0], buffer_got.length(), 
									&boardString[0], boardString.capacity());
	
	if (boardString.substr(0, 6) == L"board=") {
		boardString = boardString.substr(6, boardString.length() - 6);	

		while (*boardString.rbegin() == L'\0') {
			boardString.pop_back();
		}
		
		Board b(boardString);
		
		String answer = solver->get(b);
		std::string utf_answer;
		utf_answer.resize(WideCharToMultiByte(CP_UTF8, 0, &answer[0], answer.length(),
											   NULL, 0,  NULL, NULL));

		WideCharToMultiByte(CP_UTF8, 0, &answer[0], answer.length(),
										&utf_answer[0], utf_answer.capacity(), NULL, NULL);
		
		if (utf_answer == "") { // This happens if bomberman's still dead
			if (answer != L"") {
				throw new std::exception("Conversion from wchar_t to utf8 error!");
			}
			return;
		}
		pMsg->set_opcode(websocketpp::frame::opcode::text);
		pMsg->set_payload(utf_answer);

		std::clog << "Sending ACTION: " << pMsg->get_payload() << std::endl;
		
		websocketpp::lib::error_code err;
		c->send(hdl, pMsg->get_payload(), pMsg->get_opcode(), err);

		std::clog << "Status: " << err.message() << std::endl;
	}
}
