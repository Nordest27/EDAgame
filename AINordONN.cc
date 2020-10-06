#include "Player.hh"
#include<unordered_map>
#include<fstream>
/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME NordONN


struct NordONN : public Player 
{

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
	static Player* factory () 
	{
		return new PLAYER_NAME;
	}

  /**
   * Types and attributes for your player can be defined here.
   */
	vector<int> dw;
	vector<int> wi;
	vector<Pos> treasures;
	int  pesos[60][60];
	bool vis[60][60] { { 0 } };
	unordered_map < int, int > anterior_mov;
	float InpLay[23];
	float HidLay[23][23];
	float OutLay[23][9];
	
	int NeuralNet()
	{
		float AuxLay[23] {0};
		for ( int i = 0; i < 23; ++i )
			for ( int j = 0; j < 23; ++j )
				AuxLay[i] += InpLay[j]*HidLay[j][i];
		float res[9] {0};
		for ( int i = 0; i < 9; ++i )
			for ( int j = 0; j < 23; ++j )
				res[i] += AuxLay[j]*OutLay[j][i];
		int imax = -1;
		float max = 0, aux;
		for ( int i = 0; i < 9; ++i )
			if ( (aux = res[i]) > max )
			{
				max = aux;
				imax = i;
			}
		return imax;
		
	}
	//GENERAL
	void findTreasures()
   	{
   		for ( int i = 0; i < 60; i++ )
		   for ( int j = 0; j < 60; ++j )
				if ( cell(i,j).treasure ) treasures.push_back(Pos(i,j));
	}
	
	float dist( const Pos &p1, const Pos &p2 )
	{
  		return sqrt(pow(p1.i - p2.i, 2) + pow(p1.j - p2.j, 2));
	}
		
	int gridDist( const Pos &p1, const Pos &p2 )
	{
  		return max(abs(p1.i - p2.i), abs(p1.j - p2.j));
	}
		
	int minDistPos ( const Pos &p1, const Pos &p2 )
	{
		float min = dist(p1+Dir(0), p2), aux;
		int imin = 0;
		for ( int i = 1; i < 8; ++i ){
			if ( min > (aux = dist(p1+Dir(i), p2)) )
			{
				min = aux;
				imin = i;	
			}
		}
		return imin;	
	}
	//WIZARDS
	
	bool is_dwarf ( Pos p )
	{
		return ( cell(p).id != -1 and unit(cell(p).id).player == me() and unit(cell(p).id).type == Dwarf );
	}
	
	bool res_wizard ( Pos p )
	{
		return ( cell(p).type != Granite and cell(p).type != Rock and cell(p).type != Abyss and ( cell(p).id == -1 or  is_dwarf(p) ) );
	}
	
	int wiSensZone(const Pos& p1)
	{
		int enemy = -1;
		for ( int i = 0; i < 8; ++i )
		{
			Dir daux =  Dir(i);
			Pos paux = p1+daux;
			if ( pos_ok(paux) )
			{
				Cell caux = cell(paux);
				if ( caux.id != -1 )
				{
					Unit uaux = unit(caux.id);
					if ( uaux.player != me() ) enemy = i; 
				}
			}	
		}
		if ( enemy != -1 ) return ((enemy/2+2)%4)*2;
		else return enemy;
	}
	
	//DWARVES
	bool is_treasure( Pos p )
	{
		return cell(p).treasure;
	}
	
	bool is_enemy( Pos p )
	{
		return ( cell(p).id != -1 and unit(cell(p).id).player != me() and unit(cell(p).id).type != Balrog and unit(cell(p).id).type != Troll );
	}
	
	bool is_Troll( Pos p )
	{
		return ( cell(p).id != -1 and unit(cell(p).id).player != me() and unit(cell(p).id).type == Troll );
	}
	
	bool is_wizard( Pos p )
	{
		return ( cell(p).id != -1 and unit(cell(p).id).player == me() and unit(cell(p).id).type == Wizard );
	}	
	
	bool is_cave( Pos p )
	{
		return ( cell(p).type == Cave and cell(p).owner != me() );
	}	
	
	bool res_dwarf( Pos p, int attack )
	{
		return ( ( cell(p).type != Granite and cell(p).type != Abyss) and ( (cell(p).id == -1) or ( (attack == 1 and is_wizard(p) ) or (attack == 2 and is_enemy(p) ) ) ) );
	}
	
	int sensZone(Pos p1, bool &danger)
	{
		danger = false;
		vector<int> enemy;
		vector<int> cave;
		vector<int> rock;
		vector<int> other;
		vector<int> treasure;
		for (int i = 0; i < 8; i++){
			Dir daux =  Dir(i);
			Pos paux = p1+daux;
			if ( pos_ok(paux) )
			{
				Cell caux = cell(paux);
				if ( caux.id != -1 ){
					Unit uaux = unit(caux.id);
					if ( uaux.player != me() ) enemy.push_back(i); 
				}
				if ( caux.treasure ) treasure.push_back(i);
				if ( caux.type == Cave and caux.owner != me() and caux.id == -1) cave.push_back(i);
				if ( caux.type == Rock ) rock.push_back(i); 
				if ( caux.type == Cave and caux.id == -1 ) other.push_back(i);
			}	
		}
		int s;
		int lowest = 0;
		bool ex = false;
		if ( (s = treasure.size()) != 0 ) return treasure[random(0,s-1)];
		if ( (s = enemy.size()) != 0 )
		{
			danger = true;
			for ( int i = 1; i < s; ++i )
				if ( unit(cell(p1+Dir(enemy[i])).id).health < unit(cell(p1+Dir(enemy[lowest])).id).health )
				{
					ex = true;
					lowest = i;
				} 
			if(ex) return enemy[lowest];
			return enemy[random(0,s-1)];
		}
		if ( (s = cave.size()) != 0 ) return cave[random(0,s-1)];
		ex = (lowest = 0) ;
		if ( (s = rock.size()) != 0 )
		{
			for ( int i = 1; i < s; ++i )
			{
				if ( cell(p1+Dir(rock[i])).turns < cell(p1+Dir(rock[lowest])).turns )
				{
					ex = true;
					lowest = i;
				}
			}
			if(ex) return rock[lowest];
			return rock[random(0,s-1)];
		} 
		if ( (s = other.size()) != 0 ) return other[random(0,s-1)];
		return random(0,7);
	}
			
	struct Node
	{
		Pos pos;
		int cost;
			
		Node()
		{
			pos = Pos(-1,-1);
			cost = 2000000;
		}
		
		Node(Pos p, int c)
		{
			pos = p;
			cost = c;
		}
		
		Node(Pos p)
		{
			pos = p;
			cost = 2000000;
		}
		
		bool operator==(const Node& a) const
		{
			return pos == a.pos;
		}
	
		bool operator<(const Node& a) const
		{
			return cost > a.cost;
		}
		
	};
	
	Pos Nearby(Pos p1, int goal, int restr, bool wiz, int lim, int& D)
	{
		D = -1;
		for ( int i = 0; i < 60; ++i )
			for ( int j = 0; j < 60; ++j )
				vis[i][j] = false;
		int wizSum = 1;
		if (wiz) wizSum = 2;
		priority_queue<Node> q;
		Node naux = Node(p1,0);
		q.push(naux);
		vis[p1.i][p1.j] = true;
		return NearbyAux(naux, q, goal, restr, wizSum, lim, D);
	}
	
	Pos NearbyAux(Node p1, priority_queue<Node>& q, int goal, int restr, int wizSum, int lim, int& D)
	{
		q.pop();
		if (p1.cost > lim) return Pos(-1, -1);
		Pos paux;
		for ( int i = 0; i < 8; i += wizSum )
		{	
			paux = Pos(p1.pos+Dir(i));
			bool Restr = true;
			if ( !pos_ok(paux) ) Restr = false;
			else if ( restr == -1 ) Restr = res_wizard( paux );
			else if ( restr == 0 ) Restr =  res_dwarf( paux, goal );
			if (  !vis[paux.i][paux.j] and Restr )
			{
				bool Goal = true;
				if ( goal == -1 ) Goal = is_dwarf(paux);
				else if ( goal == 0 ) Goal = is_treasure(paux);
				else if ( goal == 1 ) Goal = is_wizard(paux);
				else if ( goal == 2 ) Goal = is_enemy(paux);
				else if ( goal == 3 ) Goal = is_cave(paux);
				else if ( goal == 4 ) Goal = is_Troll(paux);
				vis[paux.i][paux.j] = true;
				int cost = p1.cost+pesos[paux.i][paux.j];
				if ( Goal )
				{
					D = cost;
					return paux;
				}
				q.push(Node(paux,cost));
			}
		}	
		while ( !q.empty() )
			if ( (paux = NearbyAux(q.top(), q, goal, restr, wizSum, lim, D )).i != -1 ) return paux;
		return Pos(-1,-1);
	}
	
	struct hash_fn
	{
		size_t operator() (const Node &node) const
		{
			size_t h1 = hash<int>()(node.pos.i);
			size_t h2 = hash<int>()(node.pos.j);

			return h1 ^ h2;
		}
	};
	
	int repath( Node& n, unordered_map<Node, Node, hash_fn>& path )
	{
		Node ant;
		while( path[ n ].pos.i != -1)
		{
			ant = n;
			n = path[n];
		}
		return minDistPos(n.pos, ant.pos);
	}
	
	int A_Star(Pos p1, Pos p2, int people)
	{
		int wizSum = 1;
		if (people == -1 or people == 2) wizSum = 2;
   		priority_queue < Node > to_vis;
   		
   		unordered_map <Node, Node, hash_fn> ant;
   		int  gScore[60][60];
   		for ( int i = 0; i < 60; i++ )
   			for ( int j = 0; j < 60; j++)
   				gScore[i][j] = 90000000;
   		gScore[p1.i][p1.j] = 0;
   		
		for ( int i = 0; i < 60; ++i )
			for ( int j = 0; j < 60; ++j )
				vis[i][j] = false;
		vis[p1.i][p1.j] = 0;
				
		ant[Node(p1,0)] = Node(Pos(-1,-1));
		to_vis.push(Node(p1, 0));
		Node end = Node(p2, 0);
		
    	while ( !to_vis.empty() )
		{
        	Node naux = to_vis.top();
        	if ( naux == end )
            	return repath( naux, ant );
        	vis[naux.pos.i][naux.pos.j] = true;
        	to_vis.pop();
        	for (int i = 0; i < 8; i += wizSum)
			{
				Pos paux = Pos(naux.pos+Dir(i));
				bool wantPeople = false;
				if ( pos_ok(paux) ){
					wantPeople = ( pos_ok(paux) and cell(paux).id == -1 );
					if ( people == -1 ) wantPeople = ( cell(paux).id == -1 or is_dwarf(paux) );
					else if ( people == 1 ) wantPeople = ( cell(paux).id == -1 or is_wizard(paux) );
					else if ( people == 2 ) wantPeople = ( cell(paux).id == -1 or is_enemy(paux) );
					else if ( people == 3 ) wantPeople = ( cell(paux).id == -1 or is_Troll(paux) );
				}
				if (  wantPeople and cell(paux).type != Abyss and cell(paux).type != Granite )
				{
					Node neig = Node(paux, gScore[naux.pos.i][naux.pos.j] + gridDist(paux, p2));
            		int Pot_gScore = gScore[naux.pos.i][naux.pos.j] + pesos[paux.i][paux.j];
            		
            		if ( Pot_gScore < gScore[paux.i][paux.j] )
					{ 
                		ant[neig] = naux;
               	 		gScore[paux.i][paux.j] = Pot_gScore;
               		 	neig.cost = Pot_gScore + gridDist(neig.pos, p2);
               		 	if(!vis[neig.pos.i][neig.pos.j]) to_vis.push(neig);
            	    }
            	}
            }
		}
    	return -1;
    }
    float mi_punct = 0;
	bool winning()
	{
		int mi_punct1  = nb_treasures(me())*10 + nb_cells(me());
		int mi_punct2 = nb_treasures((me()+1)%4)*10 + nb_cells((me()+1)%4);
		int mi_punct3 = nb_treasures((me()+2)%4)*10 + nb_cells((me()+2)%4);
		int mi_punct4 = nb_treasures((me()+3)%4)*10 + nb_cells((me()+3)%4);
		return ( mi_punct1 > mi_punct2 and mi_punct1 > mi_punct3 and  mi_punct1 > mi_punct4 );
	}
	
   	virtual void play () 
	{
		if ( round() == 0 )
		{
			ifstream rLear ("learningONN0.txt");
			float nse;
			rLear>>nse;
			for ( int i = 0; i < 23; ++i )
				for ( int j = 0; j < 23; ++j )
					rLear>>HidLay[i][j];
					
			/*if(nse != -1)
				for ( int i = 0; i < 70; ++i )
					HidLay[rand()%23][rand()%23] += ((float)(rand()%2000-1000))/1000;*/
	
			for ( int i = 0; i < 23; ++i )
				for ( int j = 0; j < 9; ++j )
					rLear>>OutLay[i][j];
			rLear.close();
			/*if(nse != -1)
				for ( int i = 0; i < 20; ++i )
					OutLay[rand()%23][rand()%9] += ((float)(rand()%2000-1000))/1000;*/

		}
		if ( round() == 199 )
		{
			mi_punct += (nb_treasures(me())*10 + nb_cells(me()))*20;
			if(winning()) mi_punct += 2000;
			cout<<nb_treasures(me())*10 + nb_cells(me())<<' '<<mi_punct<<endl;
			ofstream escLear ("learningONN1.txt");
			escLear<<mi_punct<<endl;	
			for ( int i = 0; i < 23; ++i )
			{
				for ( int j = 0; j < 23; ++j )
				{
					escLear<<' '<<HidLay[i][j];
				}
				escLear<<endl;
			}
			escLear<<endl;
			for ( int i = 0; i < 23; ++i )
			{
				for ( int j = 0; j < 9; ++j )
				{
					escLear<<' '<<OutLay[i][j];
				}
				escLear<<endl;
			}
			escLear<<endl;	//OutLay[i][j] = ((float)(random(-1000,1000)))/2000;
			escLear.close();
		}
		dw = dwarves(me());
		wi = wizards(me());
		int ds = dw.size();
		int ws = wi.size();
   		for ( int i = 0; i < 60; i++ )
   			for ( int j = 0; j < 60; j++)
   			{
   				pesos[i][j] = 20000000;
   				Pos paux = Pos(i,j);
				if ( cell(paux).type == Cave ) pesos[i][j] = 1;
				else if ( cell(paux).type == Outside) pesos[i][j] = 2;
				else if ( cell(paux).type == Rock ) pesos[i][j] = 1+cell(paux).turns;
				/*int d = dist(paux,unit(balrog_id()).pos);
				if (d != 0) d = 1000000/(d*d*d*d*d);
				else d = 20000000;
				pesos[i][j] += d;*/
   			}
		for(int i = 0; i < ds; i++)
		{
			if (anterior_mov.find(dw[i]) == anterior_mov.end()) anterior_mov[dw[i]] = -1;
			Pos paux = unit(dw[i]).pos;
			Pos tpaux = Pos(-1,-1), wpaux = tpaux, epaux = tpaux, cpaux = tpaux, trpaux = tpaux;
			int tdist = -1, wdist = -1, edist = -1, cdist = -1, trdist = -1;
			int tdir = -1, wdir = -1, edir = -1, cdir = -1, trdir = -1;
			int bdist = dist(paux, unit(balrog_id()).pos );
			epaux =  Nearby(paux, 2, 0, true,  40, edist );
			wpaux =  Nearby(paux, 1, 0, false, 30, wdist );
			tpaux =  Nearby(paux, 0, 0, false, 40, tdist );
		    cpaux =  Nearby(paux, 3, 0, false, 10, cdist );
			trpaux = Nearby(paux, 4, 0, false, 10, trdist);
			edir = minDistPos(paux, epaux);
			wdir = minDistPos(paux, wpaux);
			tdir = A_Star(paux, tpaux, 0);
			cdir = minDistPos(paux, cpaux);
			trdir = minDistPos(paux, trpaux);
			InpLay[0] = wdist;
			InpLay[1] = edist;
			InpLay[2] = tdist;
			InpLay[3] = cdist;
			InpLay[4] = trdist;
			InpLay[5] = unit(dw[i]).health;
			if ( edist != -1 ) 
			{
				InpLay[6] = unit(cell(epaux).id).health;
				InpLay[7] = unit(cell(epaux).id).player;
				if ( InpLay[7] != -1 )
				{
					InpLay[8]= nb_treasures(InpLay[7]);
					InpLay[9]= nb_cells(InpLay[7]);
				} 
				else InpLay[8] = InpLay[9] = -1;
			}
			else InpLay[9] = InpLay[8] = InpLay[7] = InpLay[6] = -1;
			InpLay[10] = round();
			InpLay[11] = ds;
			InpLay[12] = ws;
			InpLay[13] = nb_treasures(me());
			InpLay[14] = nb_cells(me());
			InpLay[15] = anterior_mov[dw[i]];
			InpLay[16] = wdir;
			InpLay[17] = edir;
			InpLay[18] = tdir;
			InpLay[19] = cdir;
			InpLay[20] = trdir;
			InpLay[21] = bdist;
			InpLay[22] = minDistPos(paux, unit(balrog_id()).pos );
			int res = NeuralNet();
			anterior_mov[dw[i]] = res;
			if ( res != -1 ) 
			{
				mi_punct++;
				command( dw[i], Dir(res) );
			}
		}
		for(int i = 0; i < ws; i++)
		{
			Pos paux = unit(wi[i]).pos;
			int sensDir = wiSensZone(paux);
			if ( sensDir != -1 ) command(wi[i], Dir(sensDir));
			else 
			{
				for ( int i = 0; i < 60; ++i )
					for ( int j = 0; j < 60; ++j )
						vis[i][j] = false;
				int ddir = -1, noUseDist;
				Pos dpaux = Nearby(paux, -1, -1, true, 1000, noUseDist);
				if ( dpaux.i != -1 ) ddir = A_Star(paux, dpaux, -1);
				if ( ddir != -1 ) command(wi[i], Dir(ddir));
				else command(wi[i], Dir(8));
			}
		}
   	}
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
