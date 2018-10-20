bool OpenSocet()
{
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult !=0)
	{
		printf("WSAStartup Echec : %d\n", iResult);
	}
}