#ifndef BlynkAPIHandler_h
#define BlynkAPIHandler_h

  class BlynkAPIHandler {
    public:
      BlynkAPIHandler(const char* apiEndpoint, const char* apiToken, int port);
      void sendValue(char* pin, float value);
      int readValue(char* pin);
    private:
      const char* _endPoint;
      const char* _token;
      int _port;
  };
#endif
