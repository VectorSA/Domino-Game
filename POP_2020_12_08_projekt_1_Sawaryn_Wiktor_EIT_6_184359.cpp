//POP_2020_12_08_projekt_1_Sawaryn_Wiktor_EIT_6_184359_Dev-C++ 5.11_TDM-GCC 4.9.2 64-bit Release
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <math.h>

using namespace std;

//funkcja przypisuj¹ca graczowi do rêki 7 kamyków
void randomTilesAssigmentPlayer(int hand[], int &avTiles, int T[]){
    for(int i = 0 ; i<7 ; i++){
        int index = rand() %avTiles;
        hand[i] = T[index];
        avTiles--;
        for(int i = index; i<avTiles ; i++) T[i] = T[i+1];
    }
}
//funkcja przypisujaca AI do rêki po 7 kamyków (ilosæ graczy AI zale¿y od u¿ytkownika)
int **randomTilesAssigmentAIP(int AIPcount, int &avTiles, int T[]){
    int **AIP = new int*[AIPcount];
    for(int i = 0 ; i<AIPcount ; i++) AIP[i] = new int[28];
    for(int j = 0 ; j<AIPcount ; j++) {
        for (int i = 0; i < 7; i++) {
            int index = rand() % avTiles;
            AIP[j][i] = T[index];
            avTiles--;
            for (int i = index; i < avTiles; i++) T[i] = T[i + 1];
        }
    }

    return AIP;
}
//funkcja pokazuje talon gracza
void showPlayerHand(int pH[] , int pTcount){
    for(int i = 0; i<pTcount ; i++) cout << i+1 << ". |" << floor(pH[i]/10) << "|" << pH[i]%10 << "|  ";
}
//funkcja sprawdza czy dany ruch jest mo¿liwy
bool checkIfMoveIsPossible(int tilesOnBoard[], int tilesOnBoardC, int &playerTile , char side){
    if(side == 'L'){
        if(playerTile%10 == floor(tilesOnBoard[0]/10)) return true;
        if(floor(playerTile/10) == floor(tilesOnBoard[0]/10)){
            playerTile = playerTile%10*10 + floor(playerTile/10);
            return true;
        }
    }
    if(side == 'P'){
        if(playerTile%10 == tilesOnBoard[tilesOnBoardC-1]%10) {
            playerTile = playerTile%10*10 + floor(playerTile/10);
            return true;
        }
        if(floor(playerTile/10) == tilesOnBoard[tilesOnBoardC-1]%10) return true;
    }
    return false;
}
//w tej funkcji odbywa siê tura gracza(wybór kamyka oraz strona jego usytu³owania
bool playerMove(int &playerTilesC, int pH[], int tilesOnBoard[] , int &tilesOnBoardC, int T[], int & avTiles, bool firstMove){
    int move;
    cout << "Wybierz kamien, ktory chcesz dodac (jesli nie mozesz wstawic zadnego, wcisnij '0' zeby dobrac kamien ze stosu badz pominac ture)" << endl;
    cin >> move;
    while(move < 0 || move > playerTilesC || (firstMove && move == 0)){
        cout << "Wybierz kamien, ktory chcesz dodac (jesli nie mozesz wstawic zadnego, wcisnij '0' zeby dobrac kamien ze stosu badz pominac ture)" << endl;
        cin >> move;
    }
    if(firstMove){
        tilesOnBoard[tilesOnBoardC] = pH[move - 1];
        tilesOnBoardC++;
        playerTilesC--;
        for (int i = move - 1; i < playerTilesC; i++) pH[i] = pH[i + 1];
    }
    else{
        if(move == 0){
            if(avTiles > 0){
                int index = rand()%avTiles;
                pH[playerTilesC] = T[index];
                avTiles--;
                playerTilesC++;
                for (int i = index; i < avTiles; i++) T[i] = T[i + 1];
            }
        }
        else {
            char side;
            cout << "Po ktorej stronie umiescic kamien? L-lewej, P-prawej" << endl;
            cin >> side;
            while (!(side == 'L' || side == 'P')) {
                cout << "Po ktorej stronie umiescic kamien? L-lewej, P-prawej" << endl;
                cin >> side;
            }
            if (!checkIfMoveIsPossible(tilesOnBoard, tilesOnBoardC, pH[move - 1], side)){
                cout << "Nie mozna wykonac takiego ruchu" << endl;
                return false;
            }
            else {
                if (side == 'L') {
                    for (int i = tilesOnBoardC; i >= 1; i--) tilesOnBoard[i] = tilesOnBoard[i - 1];
                    tilesOnBoard[0] = pH[move - 1];
                    tilesOnBoardC++;
                    playerTilesC--;
                    for (int i = move - 1; i < playerTilesC; i++) pH[i] = pH[i + 1];
                } else {
                    tilesOnBoard[tilesOnBoardC] = pH[move - 1];
                    tilesOnBoardC++;
                    playerTilesC--;
                    for (int i = move - 1; i < playerTilesC; i++) pH[i] = pH[i + 1];
                }
            }
        }
    }
    return true;
}
//w tej funkcji wykonuje sie tura AI
void AIPlayerMove(int ** AIP, int AIPtilesC[], int AIPcount, int tilesOnBoard[], int &tilesOnBoardC, int T[], int &avTiles){
    for(int i = 0; i<AIPcount ; i++){
        bool TileAdded = false;
        for(int j = 0 ; j < AIPtilesC[i]; j++){
            if(!TileAdded){
                if(checkIfMoveIsPossible(tilesOnBoard,tilesOnBoardC,AIP[i][j], 'L')){
                    for(int z = tilesOnBoardC; z>=1 ; z--) tilesOnBoard[z] = tilesOnBoard[z-1];
                    tilesOnBoard[0] = AIP[i][j];
                    tilesOnBoardC++;
                    AIPtilesC[i]--;
                    for(int z = j ; z<AIPtilesC[i] ; z++) AIP[i][z] = AIP[i][z+1];
                    TileAdded = true;
                    break;
                }
            }
            if(!TileAdded){
                if(checkIfMoveIsPossible(tilesOnBoard,tilesOnBoardC,AIP[i][j], 'P')){
                    tilesOnBoard[tilesOnBoardC] = AIP[i][j];
                    tilesOnBoardC++;
                    AIPtilesC[i]--;
                    for(int z = j ; z<AIPtilesC[i] ; z++) AIP[i][z] = AIP[i][z+1];
                    TileAdded = true;
                    break;
                }
            }
        }
        if(!TileAdded) {
            if(avTiles > 0){
                int index = rand()%avTiles;
                AIP[i][AIPtilesC[i]] = T[index];
                avTiles--;
                AIPtilesC[i]++;
                for (int z = index; z < avTiles; z++) T[z] = T[z + 1];
                cout <<"AI "<<i+1<<" dobralo"<<endl;
            }
            else cout <<"AI "<<i+1<<" pominelo ture" << endl;
        }
    }
}
//funkcja sprawdza czy gra siê zakoñczy³a
bool checkIfGameIsOver(int playerTilesC, int AIPtilesC[], int AIPcount){
    if(playerTilesC == 0) return true;
    for(int i = 0 ; i<AIPcount ; i++) if(AIPtilesC[i] == 0) return true;
    return false;
}
//funkcja tworzy tablicê przedstawiaj¹c¹ aktualny obraz gry
void makeBoard(char board[][364], int tilesOnBoardC, int tilesOnBoard[]){
    int tile[2];
    for(int i = 0; i<=tilesOnBoardC; i++){
        int index = i*13;
        tile[0] = floor(tilesOnBoard[i]/10);
        tile[1] = tilesOnBoard[i]%10;
        board[0][index] = '|';
        board[1][index] = '|';
        board[2][index] = '|';
        for(int j = 0 ; j<2 ; j++) {
            index = index + j*6;
            if (tile[j] == 0){
                for(int z = 0 ; z<3 ; z++) {
                    board[z][index + 1] = ' ';
                    board[z][index + 2] = ' ';
                    board[z][index + 3] = ' ';
                    board[z][index + 4] = ' ';
                    board[z][index + 5] = ' ';
                }
            }
            else if(tile[j] == 1) {
                for(int z = 0; z<3; z++) {
                    board[z][index+1] = ' ';
                    board[z][index+2] = ' ';
                    board[z][index+3] = ' ';
                    board[z][index+4] = ' ';
                    board[z][index+5] = ' ';
                }
                board[1][index+3] = '*';
            }
            else if(tile[j] == 2) {
                for(int z = 0; z<3; z++) {
                    board[z][index+1] = ' ';
                    board[z][index+2] = ' ';
                    board[z][index+3] = ' ';
                    board[z][index+4] = ' ';
                    board[z][index+5] = ' ';
                }
                board[0][index+2] = '*';
                board[2][index+4] = '*';
            }
            else if(tile[j] == 3) {
                for(int z = 0; z<3; z++) {
                    board[z][index+1] = ' ';
                    board[z][index+2] = ' ';
                    board[z][index+3] = ' ';
                    board[z][index+4] = ' ';
                    board[z][index+5] = ' ';
                }
                board[0][index+2] = '*';
                board[1][index+3] = '*';
                board[2][index+4] = '*';
            }
            else if(tile[j] == 4) {
                for(int z = 0; z<3; z++) {
                    board[z][index+1] = ' ';
                    board[z][index+2] = '*';
                    board[z][index+3] = ' ';
                    board[z][index+4] = '*';
                    board[z][index+5] = ' ';
                }
                board[1][index+2] = ' ';
                board[1][index+4] = ' ';
            }
            else if(tile[j] == 5) {
                for(int z = 0; z<3; z++) {
                    board[z][index+1] = ' ';
                    board[z][index+2] = '*';
                    board[z][index+3] = ' ';
                    board[z][index+4] = '*';
                    board[z][index+5] = ' ';
                }
                board[1][index+2] = ' ';
                board[1][index+3] = '*';
                board[1][index+4] = ' ';
            }
            else if(tile[j] == 6) {
                for (int z = 0; z < 3; z++) {
                    board[z][index + 1] = ' ';
                    board[z][index + 2] = '*';
                    board[z][index + 3] = ' ';
                    board[z][index + 4] = '*';
                    board[z][index + 5] = ' ';
                }
            }
            board[0][index+6] = '|';
            board[1][index+6] = '|';
            board[2][index+6] = '|';
        }
    }
}
//wyœwietlenie aktualnego obrazu gry
void drawBoard(char board[][364], int tilesOnBoardCount){
    for(int i = 0; i<tilesOnBoardCount*13; i++) cout << "-";
    cout << endl;
    for(int i = 0; i<3; i++){
        for(int j=0; j<tilesOnBoardCount*13 ; j++) cout <<board[i][j];
        cout << endl;
    }
    for(int i = 0; i<tilesOnBoardCount*13; i++) cout << "-";
    cout << endl;
}

int main()
{
    int tiles[] = {0,1,2,3,4,5,6,11,12,13,14,15,16,22,23,24,25,26,33,34,35,36,44,45,46,55,56,66};
    int tilesOnBoardCount = 0;
    int availableTiles = 28;
    int playerHand[28];
    int playerTilesCount;
    int AIPlayersCount;
    int **AIPlayersHand;
    int AIPlayerTilesCount[3];
    int tilesOnBoard[28];
    char board[3][364];
    bool gameOn = true;
    bool firstMove = true;

    cout << "Wprowadz liczbe graczy komputerowych (1-3)" << endl;
    cin >> AIPlayersCount;
    while(AIPlayersCount < 1 || AIPlayersCount > 3){
        cout << "Wprowadzono niepoprawn¹ liczbe, prosze wprowadzic liczbê jeszcze raz" << endl;
        cin >> AIPlayersCount;
    }

	srand(time(NULL));
    randomTilesAssigmentPlayer(playerHand,availableTiles,tiles);
    AIPlayersHand = randomTilesAssigmentAIP(AIPlayersCount,availableTiles,tiles);

    playerTilesCount = 7;
    for(int i = 0 ; i<AIPlayersCount ; i++) AIPlayerTilesCount[i] = 7;
	
    while(gameOn){
        makeBoard(board,tilesOnBoardCount,tilesOnBoard);
        drawBoard(board,tilesOnBoardCount);
        showPlayerHand(playerHand,playerTilesCount);
        cout << endl;

		bool correctInput = false;
		char input;
		while(!correctInput){
			cout << "Czy chcesz kontynuowac gre ? (T/N)" << endl;
			cin >> input;
			if(input == 'T' || input == 'N') correctInput = true;
		}
		if(input == 'N') break;

		
        bool correctMove = playerMove(playerTilesCount,playerHand,tilesOnBoard,tilesOnBoardCount,tiles,availableTiles,firstMove);
        while(!correctMove){
             correctMove = playerMove(playerTilesCount,playerHand,tilesOnBoard,tilesOnBoardCount,tiles,availableTiles,firstMove);
        }
        firstMove = false;

        makeBoard(board,tilesOnBoardCount,tilesOnBoard);
        drawBoard(board,tilesOnBoardCount);
        gameOn = !checkIfGameIsOver(playerTilesCount,AIPlayerTilesCount,AIPlayersCount);
        if(!gameOn) break;

        cout << "Wprowadz dowolna literke, aby przejsc do tury AI"<<endl;
        char pom[10];
        cin>>pom;

        AIPlayerMove(AIPlayersHand,AIPlayerTilesCount,AIPlayersCount,tilesOnBoard,tilesOnBoardCount,tiles,availableTiles);

        gameOn = !checkIfGameIsOver(playerTilesCount,AIPlayerTilesCount,AIPlayersCount);
        if(!gameOn) break;
    }

    if(playerTilesCount == 0) cout << "Brawo wygrales !"<<endl;
    else if(AIPlayerTilesCount[0] == 0) cout << "Przegrales, komputer 1 okazal sie lepszy"<<endl;
    else if(AIPlayerTilesCount[1] == 0) cout << "Przegrales, komputer 2 okazal sie lepszy"<<endl;
    else if(AIPlayerTilesCount[2] == 0) cout << "Przegrales, komputer 3 okazal sie lepszy"<<endl;

    return 0;
}


