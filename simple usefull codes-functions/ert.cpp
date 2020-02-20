#include <stdio.h>
#include <windows.h>

int main(void)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD temp;

    FILE *fp = fopen("utf8.txt", "rb");
    fseek(fp, 0, SEEK_END);
    size_t filesize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *buf = new char[filesize + 1];
    fread(buf, 1, filesize, fp);
    buf[filesize] = 0;

    int widesize = MultiByteToWideChar(CP_UTF8, 0, buf, -1, 0, 0);
    wchar_t *wbuf = new wchar_t[widesize * 2];
    MultiByteToWideChar(CP_UTF8, 0, buf, -1, wbuf, widesize);
    WriteConsoleW(h, wbuf, widesize, &temp, 0);

    free(buf);
    free(wbuf);

    fclose(fp);

    return 0;
}
