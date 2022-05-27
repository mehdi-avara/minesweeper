#include "SBDL.h"
#include <stdlib.h>
#include <time.h>
#define maxMapSize 25
#define bomb 9
#define window_hi 545
#define window_wi 525
#define rect_sizea 20
using namespace std;
struct playerInfo
{
    string playername;
    int mapSizex;
    int mapSizey;
    int numberOfBomb;
    int numberOfFlag;
    int score;
    int map[maxMapSize][maxMapSize];
    bool openedPlaces[maxMapSize][maxMapSize];
    bool flagArray[maxMapSize][maxMapSize];
    playerInfo*nextplayer;
    playerInfo*playerBefor;
};
struct boardstruct
{
    int score;
    string name;
}*boardpeople;
enum modes{
 menu1,loadGame2,changeUserName3,board4,newGameMenu5,gameProcess,choosexComponent7,chooseyComponent8,chooseNumberOfBomb
};
playerInfo *firstplayer = new playerInfo;
playerInfo* playerOnTrack=firstplayer;
string playerName=" player 1";
int map[maxMapSize][maxMapSize], mapSizex=25, mapSizey=25, numberOfBomb=50, numberOfFlag=0,score=0;
bool openedPlaces[maxMapSize][maxMapSize],flagArray[maxMapSize][maxMapSize];
char keyPeress()
{
    if (SBDL::keyPressed(SDL_SCANCODE_A))
        return 'A';
    if (SBDL::keyPressed(SDL_SCANCODE_B))
        return 'B';
    if (SBDL::keyPressed(SDL_SCANCODE_C))
        return 'C';
    if (SBDL::keyPressed(SDL_SCANCODE_D))
        return 'D';
    if (SBDL::keyPressed(SDL_SCANCODE_E))
        return 'E';
    if (SBDL::keyPressed(SDL_SCANCODE_F))
        return 'F';
    if (SBDL::keyPressed(SDL_SCANCODE_G))
        return 'G';
    if (SBDL::keyPressed(SDL_SCANCODE_H))
        return 'H';
    if (SBDL::keyPressed(SDL_SCANCODE_I))
        return 'I';
    if (SBDL::keyPressed(SDL_SCANCODE_J))
        return 'J';
    if (SBDL::keyPressed(SDL_SCANCODE_K))
        return 'K';
    if (SBDL::keyPressed(SDL_SCANCODE_L))
        return 'L';
    if (SBDL::keyPressed(SDL_SCANCODE_M))
        return 'M';
    if (SBDL::keyPressed(SDL_SCANCODE_N))
        return 'N';
    if (SBDL::keyPressed(SDL_SCANCODE_O))
        return 'O';
    if (SBDL::keyPressed(SDL_SCANCODE_P))
        return 'P';
    if (SBDL::keyPressed(SDL_SCANCODE_Q))
        return 'Q';
    if (SBDL::keyPressed(SDL_SCANCODE_R))
        return 'R';
    if (SBDL::keyPressed(SDL_SCANCODE_S))
        return 'S';
    if (SBDL::keyPressed(SDL_SCANCODE_T))
        return 'T';
    if (SBDL::keyPressed(SDL_SCANCODE_U))
        return 'U';
    if (SBDL::keyPressed(SDL_SCANCODE_V))
        return 'V';
    if (SBDL::keyPressed(SDL_SCANCODE_W))
        return 'W';
    if (SBDL::keyPressed(SDL_SCANCODE_X))
        return 'X';
    if (SBDL::keyPressed(SDL_SCANCODE_Y))
        return 'Y';
    if (SBDL::keyPressed(SDL_SCANCODE_Z))
        return 'Z';
    if (SBDL::keyPressed(SDL_SCANCODE_A))
        return 'A';
    if (SBDL::keyPressed(SDL_SCANCODE_0))
        return '0';
    if (SBDL::keyPressed(SDL_SCANCODE_1))
        return '1';
    if (SBDL::keyPressed(SDL_SCANCODE_2))
        return '2';
    if (SBDL::keyPressed(SDL_SCANCODE_3))
        return '3';
    if (SBDL::keyPressed(SDL_SCANCODE_4))
        return '4';
    if (SBDL::keyPressed(SDL_SCANCODE_5))
        return '5';
    if (SBDL::keyPressed(SDL_SCANCODE_6))
        return '6';
    if (SBDL::keyPressed(SDL_SCANCODE_7))
        return '7';
    if (SBDL::keyPressed(SDL_SCANCODE_8))
        return '8';
    if (SBDL::keyPressed(SDL_SCANCODE_9))
        return '9';
    if (SBDL::keyPressed(SDL_SCANCODE_BACKSPACE))
        return 8;
    if(SBDL::keyPressed(SDL_SCANCODE_ESCAPE))
        return 27;
    if (SBDL::keyPressed(SDL_SCANCODE_SPACE))
        return ' ';
    if (SBDL::keyPressed(SDL_SCANCODE_RETURN))
        return '\n';
    return 0;
}
void decideWhatToPrint( SDL_Rect eachplace,int xComponent, int yComponent,Texture flag,Texture bombPic,Texture notOpen,Texture number[8])
{

    if (openedPlaces[xComponent][yComponent])
    {
        if (map[xComponent][yComponent] == bomb)
            SBDL::showTexture(bombPic,eachplace);
        else {
            switch (map[xComponent][yComponent]) {
                case 0:SBDL::showTexture(number[0],eachplace);break;
                case 1:SBDL::showTexture(number[1],eachplace);break;
                case 2:SBDL::showTexture(number[2],eachplace);break;
                case 3:SBDL::showTexture(number[3],eachplace);break;
                case 4:SBDL::showTexture(number[4],eachplace);break;
                case 5:SBDL::showTexture(number[5],eachplace);break;
                case 6:SBDL::showTexture(number[6],eachplace);break;
                case 7:SBDL::showTexture(number[7],eachplace);break;
                case 8:SBDL::showTexture(number[8],eachplace);break;
                default:SBDL::showTexture(notOpen,eachplace);break;
            }
        }
    }
    else if (flagArray[xComponent][yComponent])
        SBDL::showTexture(flag,eachplace);
    else
        SBDL::showTexture(notOpen,eachplace);
}
void printTheMapGraphic(SDL_Rect eachplace,Texture flag,Texture bombPic,Texture notOpen,Texture number[8])
{
    for (int xComponent = 0; xComponent < mapSizex; xComponent++)
        for (int yComponent = 0; yComponent < mapSizey; yComponent++)
        {
            eachplace.x=xComponent * (eachplace.w+1);
            eachplace.y=yComponent*(eachplace.w+1);
            decideWhatToPrint(eachplace,xComponent, yComponent,flag, bombPic, notOpen, number);
        }

}
void placeBombs()
{

    for (int i = 0; i < numberOfBomb; i++)
    {
        int xComponent = rand() % mapSizex;
        int yComponent = rand() % mapSizey;
        if (map[xComponent][yComponent] == bomb)
            i--;
        map[xComponent][yComponent] = bomb;
    }
}
int placeOneNumber(int xComponent, int yComponent)
{
    if (map[xComponent][yComponent] == bomb)
        return bomb;
    int round[8][2] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}}, number = 0;
    for (int i = 0; i < 8; i++)
    {
        if ((xComponent + round[i][0] < 0) || (xComponent + round[i][0] >= mapSizex))
            continue;
        else if ((yComponent + round[i][1] < 0) || (yComponent + round[i][1] >= mapSizey))
            continue;
        else if (map[xComponent + round[i][0]][yComponent + round[i][1]] == bomb )
            number++;
    }
    return number;
}
void placeAllNumbers()
{
    for (int i = 0; i < mapSizex; i++)
        for (int j = 0; j < mapSizey; j++)
            map[i][j] = placeOneNumber(i, j);
}
void initializeMap(bool map[][maxMapSize],bool x)
{
    for (int i = 0; i < mapSizex; i++)
        for (int j = 0; j < mapSizey; j++)
            map[i][j] = x;
}
void initializeMap(int map[][maxMapSize])
{
    for (int i = 0; i < mapSizex; i++)
        for (int j = 0; j < mapSizey; j++)
            map[i][j] = 0;
}
void startInitializer( )
{
    initializeMap(map);
    initializeMap(openedPlaces,false);
    initializeMap(flagArray,false);
    placeBombs();
    placeAllNumbers();
}
void showZeros(int xComponent, int yComponent)
{
    if (openedPlaces[xComponent][yComponent])
        return;
    openedPlaces[xComponent][yComponent] = true;
    int round[8][2] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
    for (int i = 0; i < 8; i++)
    {
        if ((xComponent + round[i][0] < 0) || (xComponent + round[i][0] >= mapSizex))
            continue;
        if ((yComponent + round[i][1] < 0) || (yComponent + round[i][1] >= mapSizey))
            continue;
        if (map[xComponent + round[i][0]][yComponent + round[i][1]] == 0)
            showZeros( xComponent + round[i][0], yComponent + round[i][1]);
        openedPlaces[xComponent + round[i][0]][yComponent + round[i][1]] = true;
    }
}
bool moveandcheck( int &numberOfFlag, int numberOfBomb,int rectsizes)
{
    int xComponent, yComponent;
    if(SBDL::Mouse.clicked(SDL_BUTTON_LEFT,1,SDL_RELEASED))
    {
        xComponent=(SBDL::Mouse.x)/(rectsizes+1);
        yComponent=(SBDL::Mouse.y)/(rectsizes+1);
        SBDL::updateEvents();
        if (flagArray[xComponent][yComponent]==false)
        {
            if (openedPlaces[xComponent][yComponent]!= true)
                score++;
            if(map[xComponent][yComponent]==0)
                showZeros( xComponent, yComponent);
            openedPlaces[xComponent][yComponent]=true;
            if (map[xComponent][yComponent]==bomb) {
                score--;
                return false;
            }
        }
    }
    if(SBDL::Mouse.clicked(SDL_BUTTON_RIGHT,1,SDL_RELEASED))
    {
        xComponent=(SBDL::Mouse.x)/(rectsizes+1);
        yComponent=(SBDL::Mouse.y)/(rectsizes+1);
        SBDL::updateEvents();
        if (flagArray[xComponent][yComponent])
            flagArray[xComponent][yComponent]=false;
        else if(flagArray[xComponent][yComponent]==false && numberOfFlag<numberOfBomb)
            flagArray[xComponent][yComponent]=true;
    }
    return true;
}
void saveTheMap()
{
    playerOnTrack->playername=playerName;
    playerOnTrack->mapSizey=mapSizey;
    playerOnTrack->mapSizex=mapSizex;
    playerOnTrack->numberOfBomb=numberOfBomb;
    playerOnTrack->numberOfFlag=numberOfFlag;
    playerOnTrack->score=score;
    for (int i = 0; i <mapSizex ; ++i) {
        for (int j = 0; j < mapSizey; ++j) {
            playerOnTrack->map[i][j]=map[i][j];
            playerOnTrack->flagArray[i][j]=flagArray[i][j];
            playerOnTrack->openedPlaces[i][j]=openedPlaces[i][j];
        }
    }
}
void changeTheuserNameInetilizer()
{
    saveTheMap();
    int i=0;
    playerOnTrack=firstplayer;
    while (playerOnTrack->nextplayer!=NULL)
        playerOnTrack=playerOnTrack->nextplayer;
    playerOnTrack->nextplayer=new playerInfo;
    playerOnTrack=playerOnTrack->nextplayer;
    playerOnTrack->nextplayer=NULL;
    playerName=" ";
    score=0;
    startInitializer();
}
void swapi(boardstruct&a,boardstruct&b)
{
    boardstruct temp=a;
    a=b;
    b=temp;
}
void bubble_sort(boardstruct*a,int size) {
    for (int i = 0; i < size-1; i++)
        for (int j = 0; j <size-1-i; j++)
            if (a[j + 1].score > a[j].score)
                swapi(a[j], a[j + 1]);
}
void boardlistInetilize()
{
    playerInfo* x=playerOnTrack;
    playerOnTrack=firstplayer;
    int size =1;
    while(playerOnTrack->nextplayer!=NULL)
    {
        playerOnTrack=playerOnTrack->nextplayer;
        size++;
    }
    boardpeople=new boardstruct[size+4];
    playerOnTrack=firstplayer;
    for (int i = 0; true; ++i) {
        boardpeople[i].name=playerOnTrack->playername;
        boardpeople[i].score=playerOnTrack->score;
        if (playerOnTrack->nextplayer==NULL)
        {
            boardpeople[i+1].score=-1;
            size=i+1;
            break;
        }
        playerOnTrack=playerOnTrack->nextplayer;
    }
    playerOnTrack=x;
    bubble_sort(boardpeople,size-1);
}
modes whereMouseClickedMenu( SDL_Rect newGameRect,SDL_Rect loadGameRect,SDL_Rect changeuserNameRect,SDL_Rect boardRect,SDL_Rect exitRect)
{
    if(SBDL::mouseInRect(newGameRect))
        return newGameMenu5;
    else if(SBDL::mouseInRect(loadGameRect)) {
        saveTheMap();
        playerOnTrack = firstplayer;
        return loadGame2;
    }
    else if(SBDL::mouseInRect(changeuserNameRect)) {
        changeTheuserNameInetilizer();
        return changeUserName3;
    }
    else if(SBDL::mouseInRect(boardRect)) {
        boardlistInetilize();
        return board4;
    }
    else if(SBDL::mouseInRect(exitRect))
        exit(0);
    return menu1;
}
modes changeName()
{
    char holder = keyPeress();
    if (holder != 0 && holder != '\n' && holder!=8)
        playerName.push_back(holder);
    else if (holder==8)
        playerName.pop_back();
    else if (holder=='\n')
        return menu1;
    return changeUserName3;
}
modes showMenu(modes mode,Font* font,Texture newGame,Texture loadGame,Texture changeuserName,Texture board,Texture exit)
{
    SDL_Rect newGameRect={75,83,145,22};
    SDL_Rect loadGameRect={75,130,150,22};
    SDL_Rect changeuserNameRect={75,331,249,29};
    SDL_Rect boardRect={75,388,79,22};
    SDL_Rect exitRect={75,441,53,22};
    SBDL::showTexture(newGame,newGameRect);
    SBDL::showTexture(loadGame,loadGameRect);
    SBDL::showTexture(changeuserName,changeuserNameRect);
    SBDL::showTexture(board,boardRect);
    SBDL::showTexture(exit,exitRect);
    if(SBDL::Mouse.clicked(SDL_BUTTON_LEFT,1,SDL_RELEASED))
    {
        modes holder= whereMouseClickedMenu( newGameRect, loadGameRect, changeuserNameRect, boardRect, exitRect);
        SBDL::updateEvents();
        return holder;
    }
}
modes keypressloadGame(Font *font)
{
    Texture scoretxt=SBDL::createFontTexture(font, "score:"+to_string(score),255,255,255);
    SBDL::showTexture(scoretxt,350,80);
    Texture playertext = SBDL::createFontTexture(font, playerName, 255, 255, 255);
    SBDL::showTexture(playertext,75,340);
    SDL_Rect  nextkey={350,340,80,33};
    Texture nexttext = SBDL::createFontTexture(font, "Next", 255, 255, 255);
    SBDL::showTexture(nexttext,nextkey);
    SDL_Rect  backkey={350,440,80,33};
    Texture backtext = SBDL::createFontTexture(font, "Back", 255, 255, 255);
    SBDL::showTexture(backtext,backkey);
    SDL_Rect loadkey={75,440,80,33};
    Texture Loadtext = SBDL::createFontTexture(font, "Load", 255, 255, 255);
    SBDL::showTexture(Loadtext, loadkey);
    if(SBDL::Mouse.clicked(SDL_BUTTON_LEFT,1,SDL_RELEASED))
    {
        if (SBDL::mouseInRect(loadkey))
            return gameProcess;
        if(SBDL::mouseInRect(nextkey))
            if (playerOnTrack->nextplayer!=NULL) {
                playerOnTrack = playerOnTrack->nextplayer;
                return loadGame2;
            }
        if (SBDL::mouseInRect(backkey))
        {
            if (playerOnTrack->playerBefor!=NULL)
                playerOnTrack=playerOnTrack->playerBefor;
        }
        SBDL::updateEvents();
    }
    return loadGame2;
}
modes loadGameFunc(Font *font)
{
    playerName=playerOnTrack->playername;
    mapSizex=playerOnTrack->mapSizex;
    mapSizey=playerOnTrack->mapSizey;
    numberOfBomb=playerOnTrack->numberOfBomb;
    numberOfFlag=playerOnTrack->numberOfFlag;
    score=playerOnTrack->score;
    if (playerOnTrack->nextplayer!=NULL)
        playerOnTrack->nextplayer->playerBefor = playerOnTrack;
    for (int i = 0; i <mapSizex; ++i) {
        for (int j = 0; j < mapSizey; ++j) {
            map[i][j]=playerOnTrack->map[i][j];
            openedPlaces[i][j]=playerOnTrack->openedPlaces[i][j];
            flagArray[i][i]=playerOnTrack->flagArray[i][j];
        }
    }
    if (SBDL::keyReleased(SDL_SCANCODE_SPACE))
        return menu1;
    return keypressloadGame(font);
}
modes boardfunc(Font*font)
{
    for (int i = 0; boardpeople[i].score!=-1; ++i) {
        Texture namestr=SBDL::createFontTexture(font,boardpeople[i].name+" score is "+ to_string(boardpeople[i].score),255,255,255);
        int y=75+i*35;
        SBDL::showTexture(namestr,75,y);
    }
    if (SBDL::keyPressed(SDL_SCANCODE_SPACE))
    {
        delete []boardpeople;
        return menu1;
    }
    return board4;
}
modes newGameMenu(Texture easy5,Texture hard10,Texture hard15,Texture costum)
{
    SDL_Rect easyModeRect={75,83,145,22};
    SDL_Rect hard10ModeRect={75,130,145,22};
    SDL_Rect hard15modeRect={75,331,145,22};
    SDL_Rect costumRect={75,388,145,22};
    SBDL::showTexture(easy5,easyModeRect);
    SBDL::showTexture(hard10,hard10ModeRect);
    SBDL::showTexture(hard15,hard15modeRect);
    SBDL::showTexture(costum,costumRect);
    if(SBDL::Mouse.clicked(SDL_BUTTON_LEFT,1,SDL_RELEASED))
    {
        if (SBDL::mouseInRect(easyModeRect))
        {
            mapSizey=5;
            mapSizex=5;
            numberOfBomb=4;
            numberOfFlag=0;
            startInitializer();
            SBDL::updateEvents();
            return gameProcess;
        }
        if (SBDL::mouseInRect(hard10ModeRect))
        {
            mapSizey=12;
            mapSizex=12;
            numberOfBomb=28;
            numberOfFlag=0;
            startInitializer();
            SBDL::updateEvents();
            return gameProcess;
        }
        if (SBDL::mouseInRect(hard15modeRect))
        {
            mapSizey=20;
            mapSizex=20;
            numberOfBomb=96;
            numberOfFlag=0;
            startInitializer();
            SBDL::updateEvents();
            return gameProcess;
        }
        if (SBDL::mouseInRect(costumRect))
        {
            mapSizey=0;
            mapSizex=0;
            numberOfBomb=0;
            numberOfFlag=0;
            SBDL::updateEvents();
            return choosexComponent7;
        }
        SBDL::updateEvents();
    }
    return newGameMenu5;

}
modes choosexcomp(Font*font)
{
    Texture x=SBDL::createFontTexture(font,"Enter X component:"+ to_string(mapSizex),255,255,255);
    SBDL::showTexture(x,75,83);
    char holder = keyPeress();
    if (holder <='9'&&holder>='0') {
        mapSizex=mapSizex*10+holder-'0';
        if (mapSizex>25)
            mapSizex=25;
    }
    else if (holder==8)
        mapSizex=mapSizex/10;
    else if (holder=='\n')
        return chooseyComponent8;
    return choosexComponent7;
}
modes chooseycomp(Font*font)
{
    Texture x = SBDL::createFontTexture(font, "Enter Y component:" + to_string(mapSizey), 255, 255, 255);
    SBDL::showTexture(x, 75, 83);
    char holder = keyPeress();
    if (holder <='9'&&holder>='0') {
        mapSizey=mapSizey*10+holder-'0';
        if (mapSizey>25)
            mapSizey=25;
    }
    else if (holder==8)
        mapSizey=mapSizey/10;
    else if (holder=='\n')
        return chooseNumberOfBomb;
    return chooseyComponent8;
}
modes chooseNumberBomb(Font *font)
{
    Texture x = SBDL::createFontTexture(font, "Enter Number Of Bombs:" + to_string(numberOfBomb), 255, 255, 255);
    SBDL::showTexture(x, 75, 83);
    char holder = keyPeress();
    if (holder <='9'&&holder>='0') {
        numberOfBomb=numberOfBomb*10+holder-'0';
        if(numberOfBomb>(mapSizex*mapSizey-10))
            numberOfBomb=(mapSizex*mapSizey-10);
    }
    else if (holder==8)
        numberOfBomb=numberOfBomb/10;
    else if (holder=='\n')
    {
        startInitializer();
        return gameProcess;
    }
    return chooseNumberOfBomb;
}
bool isMapFull()
{
    for (int i = 0; i < mapSizex; i++)
        for (int j = 0; j < mapSizey; j++)
            if (!openedPlaces[i][j] && map[i][j]!= bomb)
                return false;
    return true;
}
modes gameProsecc(Font*font,SDL_Rect eachplace,Texture flag,Texture bombPic,Texture notOpen,Texture number[8],int rectsizes)
{
    printTheMapGraphic( eachplace, flag, bombPic, notOpen, number);
    if(isMapFull())
    {
        initializeMap(openedPlaces,true);
        printTheMapGraphic(eachplace, flag, bombPic, notOpen, number);
        Texture youWon = SBDL::createFontTexture(font,"You Won The game",255,0,255);
        SBDL::showTexture(youWon,75,window_hi-22);
        SBDL::updateRenderScreen();
        SBDL::delay(3000);
        return menu1;
    }
    if(!moveandcheck(numberOfFlag, numberOfBomb,rectsizes))
    {
        initializeMap(openedPlaces,true);
        printTheMapGraphic(eachplace, flag, bombPic, notOpen, number);
        Texture youLost = SBDL::createFontTexture(font,"you stepped on a mine",255,0,255);
        SBDL::showTexture(youLost,75,window_hi-22);
        SBDL::updateRenderScreen();
        SBDL::delay(3000);
        return menu1;
    }
    Texture scoreTexture = SBDL::createFontTexture(font,"score:"+ to_string(score),255,255,255);
    SBDL::showTexture(scoreTexture,80,window_hi-22);
    if (keyPeress()==' ')
        return menu1;
    return gameProcess;

}
int main(int argc, char *argv[])
{
    srand(time(0));
    playerOnTrack=firstplayer;
    playerOnTrack->playername=playerName;
    playerOnTrack->playerBefor=NULL;
    playerOnTrack->nextplayer=NULL;
    int rectsizes = rect_sizea;
    const int window_width = window_wi,window_height = window_hi;
    SDL_Rect backGroundRec = {0,0,window_width,window_height};
    SDL_Rect eachplace = {0,0,rectsizes,rectsizes};
    SDL_Rect eachplaceload = {0,0,8,8};
    SBDL::InitEngine("minesweeper", window_width, window_height);
    const int FPS = 20;
    const int delay = 1000 / FPS;
    Texture flag= SBDL::loadTexture("assets/flag.jpg");
    Texture notOpen= SBDL::loadTexture("assets/beforeOpenning.jpg");
    Texture bombPic= SBDL::loadTexture("assets/bomb.jpg");
    Texture backGroundPic= SBDL::loadTexture("assets/background.png");
    Texture newGame=SBDL::loadTexture("assets/New Game.png");
    Texture loadGame=SBDL::loadTexture("assets/Load Game.png");
    Texture exit=SBDL::loadTexture("assets/Exit.png");
    Texture board=SBDL::loadTexture("assets/Board.png");
    Texture changeuserName =SBDL::loadTexture("assets/Change User Name.png");
    Texture easy5=SBDL::loadTexture("assets/easy.png");
    Texture hard10=SBDL::loadTexture("assets/hard.png");
    Texture hard15=SBDL::loadTexture("assets/hard15.png");
    Texture costum=SBDL::loadTexture("assets/custom.png");
    Texture changeuserName2 =SBDL::loadTexture("assets/Change User Name.png");
    Font *font = SBDL::loadFont("assets/times.ttf",20);
    Texture number[8];
    for (int i = 0; i <9; ++i) {
        number[i]=SBDL::loadTexture("assets/number"+ to_string(i)+".jpg");
    }
    int now = SBDL::getTime();
    modes mode=menu1;
    while (SBDL::isRunning()) {
        int startTime = SBDL::getTime();

        SBDL::updateEvents();
        SBDL::clearRenderScreen();
        SBDL::showTexture(backGroundPic,backGroundRec);
        switch (mode) {
            case menu1:mode= showMenu(mode,font,newGame,loadGame,changeuserName,board,exit);break;
            case newGameMenu5:mode =newGameMenu( easy5, hard10, hard15, costum);break;
            case choosexComponent7:mode=choosexcomp(font);break;
            case chooseyComponent8:mode=chooseycomp(font);break;
            case chooseNumberOfBomb:mode=chooseNumberBomb(font);break;
            case gameProcess:mode=gameProsecc(font,eachplace,flag,bombPic,notOpen,number,rectsizes);break;
            case loadGame2:printTheMapGraphic( eachplaceload, flag, bombPic, notOpen, number);
                mode= loadGameFunc(font);break;
            case board4:mode= boardfunc(font);break;
            case changeUserName3:            Texture nameTexture= SBDL::createFontTexture(font,playerName,255,255,255);
                SBDL::showTexture(nameTexture,75,83);
                mode=changeName();
                mode= mode;break;
        }
        Texture timeer = SBDL::createFontTexture(font,  to_string((SBDL::getTime() - now)/1000),225,225,225);
        SBDL::showTexture(timeer,10,window_height-22);
        Texture nameTexture= SBDL::createFontTexture(font,  playerName,225,225,225);
        SBDL::showTexture(nameTexture,160,window_height-22);
        SBDL::updateRenderScreen();
        int elapsedTime = SBDL::getTime() - startTime;
        if (elapsedTime < delay)
            SBDL::delay(delay - elapsedTime);
    }
}


