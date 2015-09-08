//#include <stdio.h>

//#include <sys/types.h>
//#include <unistd.h>
//#include <sys/sendfile.h>

#include <netdb.h>
#include <iostream>
#include <sys/socket.h>


#define DEBUG
#ifdef DEBUG

#define DEBUG_FUCKN
#define DEBUG_GETHOST

#include <arpa/inet.h>
#endif

struct linkStruct
{
    std::string protocol = "";
    std::string hostname = "";
    std::string relative = "";
    std::string filename = "";
};
struct requestSkeleton
{
    std::string method = "GET";
    char SP = char(32);
    std::string httpVer = "HTTP/1.1";
    std::string requestHeader = "\r\nAccept: */*\r\nAccept-Charset: utf-8\r\nConnection: Keep-Alive\r\n";
    std::string CRLF = "\r\n\r\n";
    int flags = 0;
};

void show_help(char* cmdname);
int gethost(char* address, linkStruct *result);
void log(std::string message);
void log(FILE * fd, std::string message);

int main (int argc, char* argv[])
{

    if (argc < 2) {

        fprintf(stderr, "%i : %s\n", argc, argv[argc - 1]);
        show_help(argv[0]);
#        ifdef DEBUG
            argv[1] = (char *)"https://pp.vk.me/c623120/v623120157/465ee/c5fCboWQibg.jpg";
            argc += 1;
#        else
            return -1;
#        endif
    }

    int temporaryInteger = 1;

    linkStruct addr;

    for (int i = 1; i < argc; i++) {
        std::string s = argv[i];
        if(s == "-o") {
            addr.filename = argv[i + 1];
            i += 2;
        } else if (s.find("/") != s.npos) {
            //fprintf(stdout, "found link-like argument \"%s\"\n", argv[i] );
            temporaryInteger = i;
        }
    }

    log("found link-like " + std::string(argv[temporaryInteger]));




    temporaryInteger = gethost(argv[temporaryInteger], &addr);


    if(temporaryInteger != 0)
        return temporaryInteger;



    struct addrinfo *he = new struct addrinfo;

    he->ai_socktype = SOCK_STREAM;
    he->ai_family = AF_INET;

    temporaryInteger = getaddrinfo (addr.hostname.c_str(), "80", he, &he);

    log ("getaddrinfo done: " + std::to_string(temporaryInteger));

    if(temporaryInteger != 0) {
        //return temporaryInteger;
        temporaryInteger = getaddrinfo(addr.hostname.c_str(), "80", NULL, &he);
        log(stderr, "getaddrinfo done[+1]: " + std::to_string(temporaryInteger));
    }

    log("SOCK_DGRAM = " + std::to_string(SOCK_DGRAM));
    log("SOCK_STREAM = " + std::to_string(SOCK_STREAM));

#    ifdef DEBUG_FUCKN
        struct addrinfo * temporaryPointer = he;


        log("he->ai_socktype = " + std::to_string(he->ai_socktype));

        struct sockaddr_in *tempinadr =  (struct sockaddr_in *)he->ai_addr;

        log("struct addrinfo {"\
            "\nint     ai_flags;            " + std::to_string(he->ai_flags) +\
               "\nint     ai_family;            " + std::to_string(he->ai_family) +\
            "\nint     ai_socktype;            " + std::to_string(he->ai_socktype) +\
            "\nint     ai_protocol;            " + std::to_string(he->ai_protocol) +\
            "\nsize_t  ai_addrlen;            " + std::to_string(he->ai_addrlen) +\
            "\nstruct  sockaddr *ai_addr;    " + std::to_string(he->ai_addr->sa_family) + "  " + inet_ntoa(tempinadr->sin_addr));

        log("char    *ai_canonname;     /* canonical name */" \
            "\nstruct  addrinfo *ai_next; /* this struct can form a linked list */" /*+ std::to_string(he->ai_next) +*/\
            "\n}");
        delete  temporaryPointer;
#   endif



    log("he->ai_socktype = " + std::to_string(he->ai_socktype));



    ////////////////////////////////////////////////////
    //So we have host adress from link.
    int socketFd;
    socketFd = socket(he->ai_family, he->ai_socktype, he->ai_protocol);

    log("socketFd = " + std::to_string(socketFd));
    if(socketFd < 0)
    {
        log(stderr, "Error opening socketFd: " + std::to_string(socketFd));
        return 2;
    }



    if (addr.protocol != "http") {
        log("protocol егор!");
        //return 15;
    }


    log("Trying to connect..");
    temporaryInteger = connect(socketFd, he->ai_addr, he->ai_addrlen);
    log("connected; return value: " + std::to_string(temporaryInteger));
    if (temporaryInteger != 0) {
        log (stderr, "connection error, exitting");
        return 50;
    }


    //////////////////////////////////////////////////
    //Connection established. It's time to send data! ^.^
    std::string message = "";
    requestSkeleton requestSkeleton;
    message = requestSkeleton.method + requestSkeleton.SP + addr.relative + requestSkeleton.SP + requestSkeleton.httpVer
        + requestSkeleton.SP + requestSkeleton.requestHeader + "Host:" + addr.hostname + requestSkeleton.CRLF;
    log(message);

    temporaryInteger = send(socketFd, message.c_str(), message.size(), 0);
    log("Sent data: " + std::to_string(temporaryInteger));
    log("Trying to open file: " + std::string("./" + addr.filename) + "\n...");
    FILE * localFd = fopen(std::string("./" + addr.filename).c_str(), "wb+");

    if (localFd == NULL) {
        fprintf(stderr, "%s\n", "Error opening localFd");
        return 100;
    }
    log("Success.");


    ////////////////////////////////////////
    log("starting recv in a loop");
    std::string server_reply;
    char * server_reply_buf;

    while(server_reply.find("\r\n\r\n") == server_reply.npos) {
        recv(socketFd, server_reply_buf, sizeof(char), 0);
        server_reply.push_back(*server_reply_buf);
    }

    log(server_reply);
    if(server_reply.find('\0') != server_reply.npos) {
        log(stderr, "Ughm, could parse response header illegally, sry.");
    }

    server_reply.push_back('\0');
    for(int i = 0; server_reply[i] != '\0'; ++i)
        server_reply[i] = std::toupper(server_reply[i]);
    //log(server_reply);

    int temp = 0;
    int temp2 = 0;

    temp = server_reply.find("200 OK");
    if(temp == server_reply.npos)
        fprintf(stderr, "Could not find \'200 OK\' in the header.\n");



    temp = server_reply.find("CONTENT-LENGTH:");
    temp = server_reply.find(":", temp);
    temp += 2;
    temp2 = server_reply.find("\r\n", temp);

    int contentLength = stoi(server_reply.substr(temp, abs(temp2-temp)), NULL, 10);
    log(std::to_string(contentLength) + " bytes");

    contentLength = (contentLength / sizeof(char) );
    log(std::to_string(contentLength) + " chars");

    int i = 0;
    while(++i < contentLength) {
        recv(socketFd, server_reply_buf, sizeof(char), 0);
        fprintf(localFd, "%c" , *server_reply_buf);
    }
    return 0;
}




void show_help(char* cmdname) {
    fprintf(stdout, "A simple wget implementation\n" );
    fprintf(stdout, "Usage: %s ADDRESS\n", cmdname );
}



int gethost(char* address, linkStruct * result) {
    int begin = 0;
    std::string s = address;
    int end = s.size() / sizeof(char);
    int temp = 0;
    temp = s.find("//", 1);
    if (temp != s.npos)
    {
        begin = temp + 2;
        result->protocol = s.substr(0, temp - 1);
    } else {
        temp = 0;
        result->protocol = "http";
    }

    temp = s.find("/", begin + 1);
    if (temp != s.npos) {
        end = temp;
        result->hostname = s.substr(begin, abs(end - begin));
        result->relative = s.substr(end);
    }

    if(result->filename == "") {
        temp = s.rfind("/");
        end = s.find("?", temp) - 1;
        if(temp != s.npos) {
            if(end == s.npos - 1)
                result->filename = s.substr(temp + 1);

            result->filename = s.substr(temp + 1, abs(end - temp));
        } else {
            return -2;
        }
    }

#   ifdef DEBUG_GETHOST
        log("gethost returns:");
        log("begin = " + std::to_string(begin));
        log("end   = " + std::to_string(end));
        //log("ukhm, host may be the \'" + s + "\'");
        log("result->protocol = " + result->protocol);
        log("result->hostname = " + result->hostname);
        log("result->relative = " + result->relative);
        log("result->filename = " + result->filename);
#   endif
    return 0;
}

void log(std::string  message) {
#   ifdef DEBUG
        log(stdout, message);
#   endif
}
void log( FILE * fd, std::string message) {
    fprintf(fd, "%s\n", message.c_str());
}