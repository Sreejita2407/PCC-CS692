#define MQKEY 1234
#define MAXSIZE 1000
typedef struct {
	long type;
	long roll[MAXSIZE];
	char name[MAXSIZE][MAXSIZE];
	int N;
}MQ;
