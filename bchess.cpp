#include<bits/stdc++.h>
#include<SDL2/SDL.h>
using namespace std;
#define ll long long

int T=0;
int chk=0;
int mat[300][300]={0};

int s1=0,s2=0,t1=0,t2=0,p1=0,p2=0;

// start of SDL declearations
const int SRC_SIZE=128,DST_SIZE=64;
SDL_Window* Main_Window;
SDL_Renderer* Main_Renderer;
SDL_Surface* Loading_Surf;
SDL_Texture* Empty_Board;
SDL_Texture* Pieces;
SDL_Rect Src_R,Dst_R,DstInd_R;
bool running;
// end of SDL declearations

void onclick(int x,int y);
void init()
{
	Main_Window = SDL_CreateWindow("SDL_RenderCopy Example",
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 16*DST_SIZE, 14*DST_SIZE, 0);
	Main_Renderer = SDL_CreateRenderer(Main_Window, -1,SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	Loading_Surf = SDL_LoadBMP("board.bmp");
	Empty_Board = SDL_CreateTextureFromSurface(Main_Renderer, Loading_Surf);
	SDL_FreeSurface(Loading_Surf);
	Loading_Surf = SDL_LoadBMP("pieces.bmp");
	Pieces = SDL_CreateTextureFromSurface(Main_Renderer, Loading_Surf);
	SDL_FreeSurface(Loading_Surf);
	running=1;
	Src_R.w=Src_R.h=SRC_SIZE;
	Dst_R.w=Dst_R.h=DST_SIZE;
	DstInd_R.w=DstInd_R.h=DST_SIZE*2;
	DstInd_R.x=14*DST_SIZE;
	DstInd_R.y=0;
}

void display()
{
	for(int i=1;i<=14;i++)
	{
		for(int j=1;j<=13;j++)
		{
			Dst_R.x=(j-1)*DST_SIZE;
			Dst_R.y=(i-1)*DST_SIZE;
			if(!mat[i][j])
			{
				SDL_RenderCopy(Main_Renderer, Empty_Board, NULL, &Dst_R);
			}
			else
			{
				if(i==s1&&j==s2)Src_R.x=SRC_SIZE;
				else Src_R.x=0;
				if(mat[i][j]<0)Src_R.y=SRC_SIZE;//white
				else Src_R.y=0;
				SDL_RenderCopy(Main_Renderer, Pieces, &Src_R, &Dst_R);
			}
		}
	}
	Src_R.x=0;
	if(T<2)Src_R.y=0;
	else Src_R.y=SRC_SIZE;
	SDL_RenderCopy(Main_Renderer, Pieces, &Src_R, &DstInd_R);
	SDL_RenderPresent(Main_Renderer);
}
void eventlistener()
{
	SDL_Event e;
	while( SDL_PollEvent( &e ) != 0 )
	{
		//User requests quit
		if( e.type == SDL_QUIT )
		{
			running = 0;
		}
		//User presses a key
		else if( e.type == SDL_MOUSEBUTTONDOWN)
		{
			if(e.button.x<13*DST_SIZE&&e.button.y<14*DST_SIZE)
			{
				onclick(e.button.y/DST_SIZE+1,e.button.x/DST_SIZE+1);
			}
		}
	}
}

void quit()
{
	SDL_DestroyTexture(Empty_Board);
	SDL_DestroyTexture(Pieces);
	SDL_DestroyRenderer(Main_Renderer);
	SDL_DestroyWindow(Main_Window);
	SDL_Quit();
}

int judge(){
	return 0;
}
void prepare(){
	for(int i=4;i<=10;i++){
		mat[5][i]=-1;
		mat[10][i]=1;
	}
	T=1;
}

void refresh(int n,int m){
	int cnt=0;
	for(int i=n-1;i<=n+1;i++){
		for(int j=m-1;j<=m+1;j++){
			if(i==n&&j==m) continue;
			if(mat[i][j]*mat[n][m]==-1) cnt++;
		}
	}
	if(cnt>=3) mat[n][m]=0;
}

void onclick(int x,int y){
//	cerr<<x<<' '<<y<<' '<<s1<<' '<<s2<<' '<<t1<<' '<<t2<<' '<<p1<<' '<<p2<<endl;
	if(s1==0&&s2==0){
		if(mat[x][y]==(T<2?1:-1)&&!(x==p1&&y==p2))
		{
			s1=x;
			s2=y;
		}
	}
	else{
		t1=x;t2=y;
		//给tn,tm赋值。 
		if(abs(s1-t1)+abs(s2-t2)==1&&!mat[t1][t2]&&mat[s1][s2]){
			mat[t1][t2]=mat[s1][s2];
			mat[s1][s2]=0;
			T++;
			T%=4;
			p1=t1;
			p2=t2;
			if(T%2==0)p1=p2=0;
		} //动一格合法。
		else {s1=s2=0;return;}
		
		for(int i=t1-1;i<=t1+1;i++){
			for(int j=t2-1;j<=t2+1;j++){
				if(i==t1&&j==t2) continue;
				refresh(i,j);
			}
		}
		refresh(t1,t2);
		s1=s2=0;
	}
}

void win(int winner){
	
}
void game(){
	while(running){//main loop
		eventlistener();
		display();
		if(judge()){
			win(judge());
			break;
		}
	}
}

int main(){
	
	prepare();
	init();
	game();
	quit();
	return 0;
}

