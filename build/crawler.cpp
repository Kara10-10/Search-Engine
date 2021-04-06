#include <iostream>
#include <stdexcept>
#include "easyhttpcpp/EasyHttp.h"

 std::string GetContent(std::string url)
{
	// configure http cache and connection pool instance (optional but recommended)
        easyhttpcpp::EasyHttp::Builder httpClientBuilder;
        //httpClientBuilder.setCache(pCache)
         //       .setConnectionPool(pConnectionPool);

        // create http client
        easyhttpcpp::EasyHttp::Ptr pHttpClient = httpClientBuilder.build();

        // create a new request and execute synchronously
        easyhttpcpp::Request::Builder requestBuilder;
        easyhttpcpp::Request::Ptr pRequest = requestBuilder.setUrl(url).build();
        easyhttpcpp::Call::Ptr pCall = pHttpClient->newCall(pRequest);
        easyhttpcpp::Response::Ptr pResponse = pCall->execute();

        if (!pResponse->isSuccessful()) 
		{
            std::cerr << "HTTP GET Error: (" << pResponse->getCode() << ")" << std::endl;
        } 
		else 
		{
            std::cout << "HTTP GET Success!" << std::endl;
			const std::string contentType = pResponse->getHeaderValue("Content-Type", "");
			 if (Poco::isubstr<std::string>(contentType, "text/html") != std::string::npos) 
			 {
                return pResponse->getBody()->toString();
             }
        }
        return url;
}



int main()
{
	std::cout << GetContent("https://www.google.com/") << std::endl;
	return 0;
}