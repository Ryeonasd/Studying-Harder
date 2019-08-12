#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#pragma warning(disable: 4996)
#define DATALENGTH 1000

char encoder(int basis, int data)
{
	char encodedData;
	if (basis == 0)
	{
		if (data == 0)
		{
			encodedData = 'A';
		}
		else
		{
			encodedData = 'B';
		}
	}
	else
	{
		if (data == 0)
		{
			encodedData = 'C';
		}
		else
		{
			encodedData = 'D';
		}
	}
	return encodedData;
}

int decoder(int basis, char encodedData)
{
	int decodedData;
	if (basis == 0)
	{
		if (encodedData == 'A')
		{
			decodedData = 0;
		}
		else if (encodedData == 'B')
		{
			decodedData = 1;
		}
		else
		{
			decodedData = rand() % 2;
		}
	}
	else
	{
		if (encodedData == 'C')
		{
			decodedData = 0;
		}
		else if (encodedData == 'D')
		{
			decodedData = 1;
		}
		else
		{
			decodedData = rand() % 2;
		}
	}
	return decodedData;
}

main()
{
	srand(time(NULL));
	int data[DATALENGTH], basisA[DATALENGTH], basisB[DATALENGTH], basisE[DATALENGTH], decodedData[DATALENGTH], secretKey[DATALENGTH], acquiredData[DATALENGTH], keyPosition[DATALENGTH];
	char encodedData[DATALENGTH], fakeEncodedData[DATALENGTH];
	bool isThereEve = false;
	int n = 0;
	float err = 0;

	//데이터, 기저 랜덤 생성
	for (int i = 0; i < DATALENGTH; i++)
	{
		data[i] = rand() % 2;
		basisA[i] = rand() % 2;
		basisB[i] = rand() % 2;
		basisE[i] = rand() % 2;
	}

	//Eve 유무 체크
	while (1)
	{
		char E;
		printf(" 침입자 존재 여부 [ T / F ]: ");
		scanf(" %c", &E);
		if (E == 'T')
		{
			isThereEve = true;
			break;
		}
		else if (E == 'F')
		{
			isThereEve = false;
			break;
		}
		else
		{
			printf("\nT 또는 F를 입력하십시오.\n");
		}
	}

	//Alice인코더
	for (int i = 0; i < DATALENGTH; i++)
	{
		encodedData[i] = encoder(basisA[i], data[i]);
	}

	//침입자 효과
	if (isThereEve == true)
	{
		//Eve디코더, 데이터 취득
		for (int i = 0; i < DATALENGTH; i++)
		{
			acquiredData[i] = decoder(basisE[i], encodedData[i]);
		}

		//Eve인코더
		for (int i = 0; i < DATALENGTH; i++)
		{
			fakeEncodedData[i] = encoder(basisE[i], acquiredData[i]);
		}
	}
	else {}

	//Bob디코더
	if (isThereEve == true)
	{
		for (int i = 0; i < DATALENGTH; i++)
		{
			decodedData[i] = decoder(basisB[i], fakeEncodedData[i]);
		}
	}
	else
	{
		for (int i = 0; i < DATALENGTH; i++)
		{
			decodedData[i] = decoder(basisB[i], encodedData[i]);
		}
	}
		
	//수치 확인
	if (isThereEve == true)
	{
		printf("\n\n |  data  basisA  encodedData  |  basisE  acquiredData  fakeEncodedData  |  basisB  decodedData  |\n |                             |                                         |                       |\n");
		for (int i = 0; i < DATALENGTH; i++)
		{
			printf(" |   %d      %d          %c       |    %d          %d               %c         |    %d          %d       | \n", data[i], basisA[i], encodedData[i], basisE[i], acquiredData[i], fakeEncodedData[i], basisB[i], decodedData[i]);
		}
	}
	else
	{
		printf("\n\n |  data  basisA  encodedData  |  basisB  decodedData  |\n |                             |                       |\n");
		for (int i = 0; i < DATALENGTH; i++)
		{
			printf(" |   %d      %d          %c       |    %d          %d       | \n", data[i], basisA[i], encodedData[i], basisB[i], decodedData[i]);
		}
	}

	//비밀키 생성, 위치 저장
	for (int i = 0; i < DATALENGTH; i++)
	{
		if (basisA[i] == basisB[i])
		{
			secretKey[n] = decodedData[i];
			keyPosition[n] = i;
			n++;
		}
		else {}
	}

	//비밀키 확인
	printf("\n비밀키는 [ ");
	for (int i = 0; i < n; i++)
	{
		printf("%d", secretKey[i]);
	}
	printf(" ] 입니다.\n\n");

	//에러율 확인
	for (int i = 0; i < n; i++)
	{
		if (data[keyPosition[i]] != secretKey[i])
		{
			err++;
		}
		else{}
	}
	printf("에러율은 %f 입니다.\n", err / n);
	if (err / n > 0.11)
	{
		printf("침입자가 감지되었습니다.\n\n");
	}

	system("pause");
	return 0;
}