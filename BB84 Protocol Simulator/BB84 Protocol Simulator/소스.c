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

	//������, ���� ���� ����
	for (int i = 0; i < DATALENGTH; i++)
	{
		data[i] = rand() % 2;
		basisA[i] = rand() % 2;
		basisB[i] = rand() % 2;
		basisE[i] = rand() % 2;
	}

	//Eve ���� üũ
	while (1)
	{
		char E;
		printf(" ħ���� ���� ���� [ T / F ]: ");
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
			printf("\nT �Ǵ� F�� �Է��Ͻʽÿ�.\n");
		}
	}

	//Alice���ڴ�
	for (int i = 0; i < DATALENGTH; i++)
	{
		encodedData[i] = encoder(basisA[i], data[i]);
	}

	//ħ���� ȿ��
	if (isThereEve == true)
	{
		//Eve���ڴ�, ������ ���
		for (int i = 0; i < DATALENGTH; i++)
		{
			acquiredData[i] = decoder(basisE[i], encodedData[i]);
		}

		//Eve���ڴ�
		for (int i = 0; i < DATALENGTH; i++)
		{
			fakeEncodedData[i] = encoder(basisE[i], acquiredData[i]);
		}
	}
	else {}

	//Bob���ڴ�
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
		
	//��ġ Ȯ��
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

	//���Ű ����, ��ġ ����
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

	//���Ű Ȯ��
	printf("\n���Ű�� [ ");
	for (int i = 0; i < n; i++)
	{
		printf("%d", secretKey[i]);
	}
	printf(" ] �Դϴ�.\n\n");

	//������ Ȯ��
	for (int i = 0; i < n; i++)
	{
		if (data[keyPosition[i]] != secretKey[i])
		{
			err++;
		}
		else{}
	}
	printf("�������� %f �Դϴ�.\n", err / n);
	if (err / n > 0.11)
	{
		printf("ħ���ڰ� �����Ǿ����ϴ�.\n\n");
	}

	system("pause");
	return 0;
}