/*

OberEngine Decompilation
Original Game: Purble Place

*/

#ifndef _SHAREDDIALOGS_H_
#define _SHAREDDIALOGS_H_

namespace SharedDialogs {
  namespace LoadGame {

  };

  namespace ResetStatistics {
  
  };

  class CorruptSaveDialog {
  public:
    static void Show();
  };

  namespace FatalDialog {

  };

  class CSplashScreen
  {
  public:
    void WaitForSplash();
    void CloseSplash();
  };
}

#endif // _SHAREDDIALOGS_H_
