
#include"GameConfig.h"
void GameConfig::GLTrace(char* format, ...)
{
	char *_traceFile = "C:\\Temp\\Sample_TH_game.log";
	int _traceNum = 1;

	if (!_traceNum) return;

	FILE *f = stderr;
	if (_traceFile != NULL)
	{
		if (fopen_s(&f, _traceFile, "a") != 0)
		{
			fprintf(stderr, "WARNING: Failed to open trace file '%s' for writing!\n", _traceFile);
			return;
		}
	}
	va_list ap;
	va_start(ap, format);
	fprintf(f, format, ap);
	va_end(ap);
	fprintf(f, "\n");
	if (_traceFile != NULL) fclose(f);
}

void GameConfig::GLMessage(LPCWSTR text)
{

	MessageBox(Windows::getCurrentWindows()->_hWindows, text, L"Sample TH", MB_OK);
}

void GameConfig::GLTitle(LPCWSTR text){
	SetWindowText(Windows::getCurrentWindows()->_hWindows, text);
}