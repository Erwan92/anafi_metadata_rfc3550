typedef struct rtphdr
{
  unsigned int         CC:4;
  unsigned int         X:1;
  unsigned int         P:1;
  unsigned int         version:2;
  unsigned int         PT:7;
  unsigned int         M:1;
  guint16              seq_num;
  guint32              TS;
  guint32              ssrc;
  guint16              profile;
  guint16              ext_len;

} rtphdr;
