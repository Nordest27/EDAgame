#include "Player.hh"
#include<unordered_map>
#include<fstream>
/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Bchungus_5


struct Bchungus_5 : public Player 
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
	int Gpesos[60][60];
	bool vis[60][60] { { 0 } };
	unordered_map < int, int > anterior_mov;
	vector<float> vaux = {-0.326, 0.013, -0.422, -1.132, 0.158, -0.734, -0.659, 0.418, -0.662, -0.15, -1.587, 0.63, -0.053, -0.143, 0.046, -1.412, 2.033, -1.748, -0.122, -1.56, 0.372, 0.00800002, 0.848, -0.463, -0.79, -1.045, 1.458, 0.085, -0.742, 0.602, 1.081, -0.733, -0.61, -0.436, 0.959, -1.095, -0.119, -3.16, 1.067, -0.398, -0.776, -0.178, -0.163, 1.072, 0.246, 0.432, 0.998, -0.331, -0.3, 1.65, 1.639, 1.525, -0.073, 0.995, -0.355, 0.659, -0.29, 0.508, -0.976, -0.461, -0.587, 0.363, 0.288, -0.662, 0.646, -0.939, 0.26, -1.427, -0.465, -1.33, 0.374, 0.415, -1.606, -0.154, 1.002, -0.519, -0.018, 1.961, -2.187, 0.985, 1.405, 1.612, 3.073, -0.517, -0.941, -1.147, 1.048, 1.055, -2.346, -1.129, 1.634, 0.464, -0.414, 1.044, 0.838, -0.455, 0.046, -0.497, -2.286, -0.044, -1.174, -0.274, -0.23, -0.257, -0.487, 0.733, -0.625, -0.273, 1.271, 0.652, 1.288, -0.002, -0.073, 1.175, 2.021, -0.76, 0.778, 0.816, 0.285, 0.989, -0.545, 1.02, -0.234, 1.651, 1.534, 0.568, 0.739, 0.464, 0.705, -0.434, -0.133, -1.394, 0.915, 0.117, -0.625, -1.314, -0.1, -1.374, -0.654, 0.652, -1.322, 0.372, -0.834, -0.379, 0.78, 0.403, 0.187, -0.4, 1.371, -0.681, 0.094, 0.316, -0.169, 0.37, -1.447, -1.841, -0.62, -0.00700004, -0.463, 0.928, -0.473, 0.348, 0.982, -0.448, -0.479, 0.196, -0.358, 0.385, -0.754, -0.772, -0.982, 0.682, 0.531, -0.795, 0.829, 0.047, -1.049, -0.229, -1.193, -0.216, -1.387, -0.566, -1.807, -0.546, 1.504, 1.832, 0.302, 0.042, -0.402, -0.384, -0.43, 0.284, -1.052, 0.472, 0.355, -0.621, -0.308, 1.037, 0.65, -3.536, -0.411, 0.347, -0.492, -1.033, 0.033, 1.244, 1.779, -0.935, 0.235, 0.196, 1.623, 1.497, -1.947, -0.812, 0.828, 0.378, 1.218, 0.185, -0.321, -0.228, 0.857, -0.761, 1.609, -0.044, 0.74, 1.224, 0.398, -0.27, -0.464, -1.654, 0.14, 0.742, 0.398, -0.096, -0.359, -0.415, 1.037, -0.104, -1.079, -0.089, -0.103, 0.234, -0.476, -0.041, 0.981, -0.295, -0.357, 1.313, -1.325, 1.032, -0.823, 0.205, 0.858, -0.041, -0.093, -0.285, 2.577, 0.089, -1.464, -0.484, -0.734, -0.437, -0.486, -0.982, 0.05, 0.129, -1.174, 0.471, -1.814, 0.00500003, -1.607, -0.786, 0.721, 0.217, -0.369, 0.208, 0.1, -0.85, 0.502, -0.083, -1.524, 1.126, -0.041, 0.704, 0.196, -0.765, 0.312, 1.41, 2.291, -0.462, -0.84, 1.968, -0.434, 2.142, 1.144, 0.179, -0.641, 1.27, -0.831, -0.389, -0.218, -0.906, -0.08, -1.365, -0.799, 0.895, -0.27, 0.549, -0.637, 1.114, -0.907, -0.728, 0.128, -1.504, -1.9, 2.067, -0.793, 0.385, 0.305, -2.097, 0.781, -0.678, -0.495, -0.406, -0.706, -0.238, -1.583, -0.987, 0.669, 0.265, -1.079, 0.873, -0.302, -0.379, -0.305, -1.476, 0.742, -0.194, 0.527, -1.508, -0.271, -0.372, 1.736, -0.344, -0.562, -0.749, 0.971, -0.835, -1.494, 0.513, -2.276, -1.392, -1.416, 1.116, 0.164, 1.044, 0.496, 0.796, -0.078, 0.3, -1.041, -0.598, 0.302, -0.717, 0.018, -0.44, 0.215, -0.165, 0.368, 0.517, -2.084, -0.04, 0.098, 1.568, 0.189, 0.642, 0.801, 1.577, -0.49, -0.0599999, -0.993, -0.202, 0.373, 1.74, -0.034, -0.145, 2.029, 0.109, -1.22, 0.277, 1.023, 0.833, 0.499, 1.285, 1.136, 0.505, 0.0429999, 0.175, 1.122, 0.561, 1.019, 1.337, 0.052, -0.81, 0.479, -0.029, -0.356, -0.442 };	float InpLay[17];
	float HidLay[17][17];
	float OutLay[17][7];
	
	int NeuralNet()
	{
		float AuxLay[17] {0};
		for ( int i = 0; i < 17; ++i )
			for ( int j = 0; j < 17; ++j )
				AuxLay[i] += InpLay[j]*HidLay[j][i];
		float res[7] {0};
		for ( int i = 0; i < 7; ++i )
			for ( int j = 0; j < 17; ++j )
				res[i] += AuxLay[j]*OutLay[j][i];
		int imax = -1;
		float max = 0, aux;
		for ( int i = 0; i < 7; ++i )
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
			if(ex)
			{
				if( unit(cell(p1+Dir(enemy[lowest])).id).type == Troll ) return (enemy[lowest]+4 )%8; 
				return enemy[lowest];
			}
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
	Pos GetOut( Pos p1 )//, int goal, int restr, bool wiz, int lim, int& D)
	{
		for ( int i = 0; i < 60; ++i )
			for ( int j = 0; j < 60; ++j )
				vis[i][j] = false;
		priority_queue<Node> q;
		Node naux = Node(p1,0);
		q.push(naux);
		vis[p1.i][p1.j] = true;
		return GetOutAux(naux, q, 0);
	}
	
	Pos GetOutAux( Node p1, priority_queue<Node>& q, int it )
	{
		it++;
		q.pop();
		if (it > 100) return Pos(-1, -1);
		Pos paux;
		for ( int i = 0; i < 8; i++)
		{	
			paux = Pos(p1.pos+Dir(i));

			if (  pos_ok(paux) and !vis[paux.i][paux.j] and cell(paux).type != Granite and cell(paux).type != Abyss and cell(paux).id == -1 )
			{
				vis[paux.i][paux.j] = true;
				int cost = p1.cost+Gpesos[paux.i][paux.j];
				if ( cell(paux).type == Cave and cell(paux).owner != me() and Gpesos[paux.i][paux.j] < 1500 )
					return paux;
				q.push(Node(paux,cost));
			}
		}	
		while ( !q.empty() )
			if ( (paux = GetOutAux(q.top(), q, it )).i != -1 ) return paux;
		return Pos(-1,-1);
	}
	
	
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
				}
				if (  wantPeople and cell(paux).type != Abyss and cell(paux).type != Granite )
				{
					Node neig = Node(paux, gScore[naux.pos.i][naux.pos.j] + gridDist(paux, p2));
            		int Pot_gScore = gScore[naux.pos.i][naux.pos.j] + Gpesos[paux.i][paux.j];
            		
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
			int id = 0;
			for ( int i = 0; i < 17; ++i )
				for ( int j = 0; j < 17; ++j )
				{
					HidLay[i][j] = vaux[id];
					id++;	
				}
	
			for ( int i = 0; i < 17; ++i )
				for ( int j = 0; j < 7; ++j )
				{
					OutLay[i][j] = vaux[id];
					id++;
				}

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
				if ( cell(paux).type == Cave ) Gpesos[i][j] = pesos[i][j] = 1;
				else if ( cell(paux).type == Outside) Gpesos[i][j] = pesos[i][j] = 2;
				else if ( cell(paux).type == Rock ) Gpesos[i][j] = pesos[i][j] = 1+cell(paux).turns;
				int d = dist(paux,unit(balrog_id()).pos);
				if (d != 0) d = 1000000/(d*d*d*d*d);
				else d = 20000000;
				if ( cell(paux).type == Outside) Gpesos[i][j] = 2;
				for(int i2 = 0; i2 < trolls().size(); ++i2 )
				{
					int dt = dist(paux,unit(trolls()[i2]).pos);
					if (dt != 0) dt = 10000/(dt*dt*dt);
					else dt = 20000;
					Gpesos [i][j] += dt;
				}
				Gpesos[i][j] += d;
   			}
   		for(int i = 0; i < ds; i++)
		{
			if (anterior_mov.find(dw[i]) == anterior_mov.end()) anterior_mov[dw[i]] = -1;
			Pos paux = unit(dw[i]).pos;
			bool danger;
			int sensdir = sensZone(paux, danger);
			if (danger) command(dw[i], Dir(sensdir));
		}
		
		for(int i = 0; i < ds; i++)
		{
			if (anterior_mov.find(dw[i]) == anterior_mov.end()) anterior_mov[dw[i]] = -1;
			Pos paux = unit(dw[i]).pos;
			bool danger;
			int sensdir = sensZone(paux, danger); 
			if(!danger)
			{
				Pos tpaux = Pos(-1,-1), wpaux = tpaux, epaux = tpaux, cpaux = tpaux, trpaux = tpaux, dpaux = tpaux;
				int tdist = -1, wdist = -1, edist = -1, cdist = -1, trdist = -1, ddist = -1;
				int bdist = dist( paux, unit(balrog_id()).pos );
				epaux =  Nearby(paux, 2, 0, true, 30, edist );
				wpaux =  Nearby(paux, 1, 0, false, 10, wdist );
				tpaux =  Nearby(paux, 0, 0, false, 10, tdist );
			    cpaux =  Nearby(paux, 3, 0, false, 10, cdist );
				trpaux = Nearby(paux, 4, 0, false, 10, trdist);
				dpaux =  Nearby(paux,-1, 0, false, 10, ddist );
				InpLay[0] = wdist;
				InpLay[1] = edist;
				InpLay[2] = tdist;
				InpLay[3] = cdist;
				InpLay[4] = trdist;
				InpLay[5] = unit(dw[i]).health;
				if ( edist != -1 ) 
				{
					InpLay[6] = unit(cell(epaux).id).health;
					InpLay[7] = (me() + unit(cell(epaux).id).player)%4;
					if ( unit(cell(epaux).id).player != -1 )
					{
						InpLay[8]= nb_treasures(unit(cell(epaux).id).player);
						InpLay[9]= nb_cells(unit(cell(epaux).id).player);
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
				InpLay[16] = ddist;
				int res = NeuralNet();
				anterior_mov[dw[i]] = res;
				Pos pgo = Pos (-1,-1);
				if ( res == 0 )      pgo = wpaux;
				else if ( res == 1 ) pgo = epaux;
				else if ( res == 2 ) pgo = tpaux;
				else if ( res == 3 ) pgo = cpaux;
				else if ( res == 4 ) pgo = dpaux;
				else if ( res == 5 ) pgo = GetOut(paux);
				else if ( res == 6 ) command(dw[i],Dir(sensdir));
				int people = 0;
				if ( res == 0 ) people = 1;
				else if ( res == 1 ) people = 2;
				else if ( res == 4 ) people = -1;
				if ( pgo.i != -1 )
					command( dw[i], Dir(A_Star(paux, pgo, people)) );
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
