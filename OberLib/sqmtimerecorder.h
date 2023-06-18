/*

OberEngine Decompilation
Original Game: Purble Place

*/

#ifndef _SQMTIMERECORDER_H_
#define _SQMTIMERECORDER_H_

class CSQMTimeRecorder
{
private:
  unsigned int m_iDataId; // 0
  unsigned int m_iUnused; // 1 (I doubt this is padding)
  ULONGLONG m_qTickCount; // 2

public:
  ~CSQMTimeRecorder();

  void SetDataId(unsigned int dataId);
};

#endif // _SQMTIMERECORDER_H_
