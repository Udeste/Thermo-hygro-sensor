#ifndef WifiHandler_h_
#define WIfiHandler_h_

  class WifiHandler {
    public:
      WifiHandler(const char* ssid, const char* password);
      void enable();
      void disable();
      bool connect();
      void disconnect();
    private:
      const char* _ssid;
      const char* _password;
  };
#endif
