#include <iostream>
#include <string>
#include <future>

#include <curl/curl.h>
#include <jsoncpp/json/json.h>
#include <sw/redis++/redis++.h>

using namespace std;
using namespace sw::redis;

struct walletParams {
  double final_balance;
  u_int  n_tx;
  double total_received;
};

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

walletParams decode(string text, string wallet) {
    Json::Value root;
    Json::Reader reader;
	walletParams wp;
    bool parsingSuccessful = reader.parse(text,root);
    if (!parsingSuccessful)
    {
        cout << "Error parsing the string" << endl;
    }
    const Json::Value body = root[wallet];
	wp.final_balance = body["final_balance"].asDouble();
	wp.n_tx = body["n_tx"].asInt();
	wp.total_received = body["total_received"].asDouble();
	
	return wp;
}

int main(void) { 
  	CURL *curl;
  	CURLcode res;
  	string readBuffer, wallet;
  	string base_url = "https://blockchain.info/balance?active=";
  	cout << "Enter wallet: ";
  	getline(cin, wallet);
	if (wallet.empty())
	{
		cout << "(using default wallet - Microstrategy main)" << endl;
		wallet = "1P5ZEDWTKTFGxQjZphgWPQUpe554WKDfHQ";
	}
	base_url += wallet;

	curl = curl_easy_init();

		if(curl)
		{
			curl_easy_setopt(curl, CURLOPT_URL, base_url.c_str());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
			res = curl_easy_perform(curl);
			curl_easy_cleanup(curl);

			cout << "Wallet      : " << wallet << endl;
			future<walletParams> r = async(decode, readBuffer, wallet);
			walletParams res = r.get();
			
			cout << "Balance     : " << to_string(res.final_balance) << endl;
			cout << "Transactions: " << to_string(res.n_tx) << endl;
			cout << "Tot.Received: " << to_string(res.total_received) << endl;

			auto redis = Redis("tcp://127.0.0.1:6379");
			redis.set("key", "val");
			auto val = redis.get("key");
			if (val) {
				std::cout << *val << std::endl;
			}
		}

  	return 0;
}