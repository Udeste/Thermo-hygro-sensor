#ifndef WifiHandler_h_
#define WIfiHandler_h_

  class WifiHandler {
    public:
      WifiHandler();
      void enable();
      void disable();
      bool connect(const char* ssid, const char* password);
      void disconnect();
    private:
      const char* _ssid;
      const char* _password;
  };
#endif
