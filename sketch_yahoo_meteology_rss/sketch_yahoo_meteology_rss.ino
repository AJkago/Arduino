#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <NunniMCAX.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#define MAXLEN 256

const char* ssid = "";
const char* password =  "";


static char m_characters[MAXLEN];
struct NunniMCAXContentHandler handler;
bool RootDetected = false;

void setup()  {

  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to the WiFi network");

 /* set up the paser handler functions */
  handler.startDocument = startDocument;
  handler.startElement = startElement;
  handler.characters = characters;
  handler.endElement = endElement;
  handler.endDocument = endDocument;

byte ip[] = { 192, 168, 0, 111 };
byte server[] = { 124, 83, 139, 175 };    // rss.weather.yahoo.co.jp

}

void loop()
 {
  Serial.println("##connecting...");
  if (client.connect()) {
    Serial.println("##connected");
    client.write("GET /ansi.xml HTTP/1.0\r\n\r\n");
  } else {
    Serial.println("##connection failed");
    delay(5000);
    return;
  }

  // パーサーの呼び出し
  NunniMCAXparse( &getcFunc, &handler );

  Serial.println("##disconnecting.");
  Serial.println("");
  client.stop();
  RootDetected = false;
  delay(5000);
  return;

  // Ethernetからの1文字読み取るコールバック関数
// 最初の'<'（タグの開始）まで読み飛ばし
//  → HTTPサーバーレスポンス文字を読み飛ばす
int getcFunc()
{
  while(!RootDetected)
  {
    if (getChar() == '<')
    {
      RootDetected = true;
      return '<';
    }
  }

  return getChar();
}

int getChar()
{
  if (client.available())
    return client.read();

  if (!client.connected())
    return EOF;
}
 /* SAXパーサーのイベントハンドラー */
int startDocument(void)
{
  Serial.println( "startDocument" );
  return 0;
}

int startElement( const char *tagname, struct NunniHashtable *args )
{
  const int size = NunniHashtableSize( args );
  char ** keys;
  int i, ret;
  const char *name, *value;
  keys = (char**)calloc( size, sizeof( char * ) );
  Serial.print("start element: ");
  Serial.println(tagname);
  ret = NunniHashtableKeys( args, keys );
  for ( i = 0; i < size; ++i ) {
    name = keys[i];
    value = NunniHashtableGet( args, name );
    Serial.print("  attrName: ");
    Serial.print(name);
    Serial.print("   attrValue: ");
    Serial.println(value);
  }
  memset( m_characters, 0, MAXLEN );
  return 0;
}

int characters( char ch[], int start, int length )
{
  int i = strlen( m_characters );
  if ( i == MAXLEN )
    return -1;
  strncat( m_characters, &(ch[start]), length );
  return 0;
}

int endElement( const char *tagname )
{
  int len;
  char *data = m_characters;
  while( isspace( *data ) ) {
    ++data;
  }
  len = strlen( data );
  while( isspace( data[--len] ) ) {
    data[len] = 0;
  }
  if ( data != NULL && strncmp( data, "", 1 ) )
  {
    Serial.print("text: ");
    Serial.println(data);
  }
  memset( m_characters, 0, MAXLEN );
  Serial.print("end element: ");
  Serial.println(tagname);

  return 0;
}

int endDocument(void)
{
  Serial.println( "endDocument" );
  return 0;
}

}
