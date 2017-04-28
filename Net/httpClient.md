### Get

```
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>

class HTTPGetter
{
public:
	HTTPGetter(const std::string& host, Poco::UInt16 port = Poco::Net::HTTPSession::HTTP_PORT) : mHost(host), mPort(port)
	{
	}

	~HTTPGetter()
	{
	}

	int	Get(const std::string& path, std::ostream& ostr)
	{
		try
		{
			const std::string myPath = ('/' == path.c_str()[0]) ? path:("/"+path);

			Poco::Net::HTTPClientSession session(mHost, mPort);
			Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_GET, path, Poco::Net::HTTPMessage::HTTP_1_1);
			session.sendRequest(req);
			Poco::Net::HTTPResponse res;
			std::istream& rs = session.receiveResponse(res);
			Poco::StreamCopier::copyStream(rs, ostr);
		}
		catch (Poco::Exception& exc)
		{
			return -1;
		}

		return 0;
	}

private:
	HTTPGetter();
	HTTPGetter(const HTTPGetter&);
	HTTPGetter& operator = (const HTTPGetter&);

	std::string		mHost;
	Poco::UInt16	mPort;
};



int main()
{
	//PrepareConsoleLogger logger(Poco::Logger::ROOT, Poco::Message::PRIO_INFORMATION);

	Poco::URI uri("http://poco.roundsquare.net/downloads/test.txt");
	{
		//ScopedElapsedTime msg("HTTPGetter ", "start", "end");

		HTTPGetter getter(uri.getHost(), uri.getPort());
		getter.Get(uri.getPath(), std::cout);
	}

	return 0;
}
```


### Post, ContentType("application/x-www-form-urlencoded")

```
Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_POST, uri.getPath(), Poco::Net::HTTPMessage::HTTP_1_1);

req.setContentType("application/x-www-form-urlencoded");
Poco::Net::HTMLForm form;
form.add("userName", "hello");
form.add("password", "123456");
form.prepareSubmit(req);

Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
std::ostream& ostr = session.sendRequest(req);
form.write(ostr);


Poco::Net::HTTPResponse res;
std::istream& is = session.receiveResponse(res);

std::streamsize _size = Poco::StreamCopier::copyToString( is, resultBuffer );
```
