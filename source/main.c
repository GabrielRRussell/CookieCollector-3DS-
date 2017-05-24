
#include <3ds.h>
#include <spritetools.h>
#include <stdio.h>

int main(void)
{
  int cookies = 0;
  int cookiesAdd = 1;
  int cookiesInterval = 0;
  int pointers = 0;
  int grandmas = 0;

  int second = 0;

  ST_Init();
  ST_DebugSetOn();

  while (aptMainLoop())
  {
    consoleInit(GFX_TOP, NULL);
	ST_InputScan();

	if (ST_InputButtonDown(KEY_A)) {
		cookies = cookies + cookiesAdd;
	}


    if (ST_TimeRunning() % 1000 <= 50 && second == 0)
    {
      second = 1;
      printf("\x1b[2J");
      cookies = cookies + cookiesInterval;
    }
    if (ST_TimeRunning() % 1000 > 50)
      second = 0;

    consoleInit(GFX_BOTTOM, NULL);

    if (ST_TimeRunning() % 1000 <= 50 && second == 0) {
	second = 1;
	printf("\x1b[2J");
    }
    if (ST_TimeRunning() % 1000 > 50)
	second = 0;
  }

	printf("\x1b[1;1H%d", cookies);
	printf("\x1b[2;1H%d", cookiesInterval);
  
    ST_Fini();
  return 0;
}