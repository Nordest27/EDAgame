#include<iostream>
#include<map>
#include<queue>
#include<fstream>
#include<cctype>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

void gen_random(char *s, const int len) {
    static const char num[] =
        "0123456789";

    for (int i = 0; i < len; ++i) {
        s[i] = num[rand() % (sizeof(num) - 1)];
    }

    s[len] = 0;
}

int main()
{
	vector< pair <int, vector<float> > > mats;
	vector< pair <int, vector<float> > > curBestMats;
	vector<float> vaux(513);
	float lect;
	int gen = 0;
	ifstream rLear ("learningONNBuit.txt");
	rLear>>lect;
	for(int i = 0; i < 513; ++i)
	{
		rLear>>vaux[i];
	}
	for(int i = 0; i < 10; ++i) 
		curBestMats.push_back(pair<int,vector<float> >(lect, vaux) );
	rLear.close();
	while(1){
		int s = mats.size();
		cout<<s<<endl;
		cout<<gen%100<<endl;
		if ( s > 60 )
		{
			//cout<<mats[0].first<<' '<<mats[1].first<<' '<<mats[2].first<<' '<<mats[3].first<<' '<<mats[4].first<<endl;
			sort( mats.begin(), mats.end());
			ofstream outfile ("GenONN"+to_string(gen%100)+".txt");
				outfile<<mats[0].first<<endl;
				for(int i = 0; i < 513; ++i)
				{
					if(i%16 == 0)cout<<endl;
					outfile<<mats[0].second[i]<<' ';	
				}
			outfile.close();
			cout<<mats[0].first<<endl;
			for(int i = 0; i < 513; ++i)
			{
				if(i%16 == 0)cout<<endl;
				cout<<mats[0].second[i]<<' ';	
			}
			cout<<endl<<mats[1].first<<endl;
			for(int i = 0; i < 513; ++i)
			{
				if(i%16 == 0)cout<<endl;
				cout<<mats[1].second[i]<<' ';	
			}
			cout<<endl<<mats[2].first<<endl;//' '<<mats[3].first<<' '<<mats[4].first<<endl;
			for(int i = 0; i < 513; ++i)
			{
				if(i%16 == 0)cout<<endl;
				cout<<mats[2].second[i]<<' ';	
			}
			for(int i = 0; i < 10; ++i) cout<<mats[i].first<<' ';
			cout<<endl;
			while ( mats.size() > 10 ) mats.pop_back();
			curBestMats = mats;
			while(!mats.empty())mats.pop_back();
			gen++;
			for(int i = 0; i < 10; ++i)
			{
				vaux = curBestMats[i].second;
				ofstream escLear ("learningONN0.txt");
				escLear<<-1<<endl;
				for(int i = 0; i < 513; ++i)
				{	
					if(i%16 == 0)escLear<<endl;
					escLear<<vaux[i]<<' ';	
				}
				escLear.close();
				
				char seed[6];
				gen_random(seed, 6);
				char * argv_list[] = {"Game", "NordONN","Dummy","Dummy","Dummy","-s",seed,"-i","default.cnf","-o","default3.res",NULL}; 
				if (fork() == 0) cout<<execv("./Game", argv_list )<<endl;
				wait(NULL);
				ifstream rLear2 ("learningONN1.txt");
				rLear2>>lect;
				cout<<lect<<endl;
				for(int i = 0; i < 513; ++i)
					rLear2>>vaux[i];
				rLear2.close();
				mats.push_back(pair<int,vector<float> >(-lect, vaux) );
			}
		}
		vaux = curBestMats[rand()%10].second;
		ofstream escLear2 ("learningONN0.txt");
		escLear2<<0<<endl;
		for(int i = 0; i < 80; ++i) vaux[rand()%513] += ((float)(rand()%2000-1000))/1000;
		for(int i = 0; i < 513; ++i)
		{	
			if(i%16 == 0)escLear2<<endl;
			escLear2<<vaux[i]<<' ';	
		}
		escLear2.close();
		
		char seed[6];
		gen_random(seed, 6);
		char * argv_list[] = {"Game", "NordONN","Dummy","Dummy","Dummy","-s",seed,"-i","default.cnf","-o","default3.res",NULL}; 
		if (fork() == 0) cout<<execv("./Game", argv_list )<<endl;
		wait(NULL);
		ifstream rLear2 ("learningONN1.txt");
		rLear2>>lect;
		cout<<lect<<endl;
		for(int i = 0; i < 513; ++i)
			rLear2>>vaux[i];
		rLear2.close();
		mats.push_back(pair<int,vector<float> >(-lect, vaux) );
	}
}
