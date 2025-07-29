#include "EasyAI.h"

std::string EasyAI::getNextStep(Board board) {
    // �ƶ��ķ���
    int directions[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    std::set<std::pair<int, int>> forbiddenSet = {{2,1},{4,1},{7,1},{9,1},{3,2},{8,2},{2,3},{4,3},{7,3},{9,3}};
    int AIhighestLevel =0;
    int peoplehighestLevel =0;
    int finalStep[4] = {-1,-1,-1,-1};
    std::string status = board.getBoardState();
    int nowBoard[12][5];
    // ʹ���ַ��������ָ��ַ���
    std::stringstream ss(status);
    char delimiter;
    // �����ȡ���ֲ���������
    for (int i = 0; i < 12; i++) {
        for(int j =0;j<5;j++){
            ss >> nowBoard[i][j];
            ss >> delimiter;  // ��������
        }
    }
    int enemyX = -1,enemyY=-1;
    int highestLevel = 0;
    for(int i = 0;i<6;i++){
        for(int j=0;j<5;j++){
            if(nowBoard[i][j] > 13&&nowBoard[i][j]<26&&nowBoard[i][j]-13 > highestLevel){
                if(forbiddenSet.find({i, j}) == forbiddenSet.end()){
                    highestLevel = nowBoard[i][j] - 13;
                    enemyX = i,enemyY = j;
                }
            }
        }
    }
    for(int i = 0;i<12;i++){
        for(int j=0;j<5;j++){
            if(nowBoard[i][j] > 13&&nowBoard[i][j]<23&&nowBoard[i][j]-13 > peoplehighestLevel){
                peoplehighestLevel = nowBoard[i][j]-13;
            }
            if(nowBoard[i][j] > 0&&nowBoard[i][j]<11&&nowBoard[i][j] > AIhighestLevel){
                AIhighestLevel = nowBoard[i][j];
            }
        }
    }
     // �����������·��
    int junqiStepNum = INT_MAX;
    int junqiStep[4]= {0,0,-1,-1}; // [x, y, next_x, next_y]
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 5; j++) {
            if (nowBoard[i][j] >= 1 && nowBoard[i][j] <= 10) {
                int stepNum = 0;
                int step[4]; // [x, y, next_x, next_y]
                bfsToTarget(i, j, 11, 1, nowBoard, stepNum, step);

                if (stepNum != -1 && stepNum < junqiStepNum) {
                    junqiStepNum = stepNum;
                    junqiStep[0] = step[0]; // ��ǰ����λ��
                    junqiStep[1] = step[1];
                    junqiStep[2] = step[2]; // ��һ��λ��
                    junqiStep[3] = step[3];
                }
            }
        }
    }
    //std::cout<<"���첽��"<<junqiStepNum<<std::endl;
    //for(int i =0;i<4;i++){
    // 	std::cout<<junqiStep[i]<<"  ";
    //}
    // ������˵����·��
    int enemyStepNum = INT_MAX;
    int enemyStep[4] = {0,0,-1,-1}; // [x, y, next_x, next_y]
    if (enemyX != -1) {
        for (int i = 0; i < 12; i++) {
            for (int j = 0; j < 5; j++) {
                if (nowBoard[i][j] >= 1 && nowBoard[i][j] <= 10) {
                    int stepNum = 0;
                    int step[4]; // [x, y, next_x, next_y]
                    bfsToTarget(i, j, enemyX, enemyY, nowBoard, stepNum, step);
                    //std::cout<<stepNum<<std::endl;
                    if (stepNum != -1 && stepNum < enemyStepNum) {
                        enemyStepNum = stepNum;
                        enemyStep[0] = step[0]; // ��ǰ����λ��
                        enemyStep[1] = step[1];
                        enemyStep[2] = step[2]; // ��һ��λ��
                        enemyStep[3] = step[3];
                    }
                }
            }
        }
    }
   // std::cout<<"ɱ�в���"<<enemyStepNum<<std::endl;
    //for(int i =0;i<4;i++){
    //	std::cout<<enemyStep[i]<<"  ";
    int distance = 100;
    if(enemyX!=-1){ //�Է����ӽ����ҷ����� (������Ӫ��)
        if(enemyStepNum<=3){//���ɱ�����ҷ���ص�������Ҫ3������
            if(enemyStepNum <junqiStepNum ){//ɱ���첽���໹��ɱ�����Ӳ�����
                for(int i = 0;i<4;i++){
                    finalStep[i] = enemyStep[i];
                }
            }else{//ɱ�������
                for(int i = 0;i<4;i++){
                    finalStep[i] = junqiStep[i];
                }
            }
        }else{//��Ҫ4����������
            if(highestLevel+13 >= 18){//����Ϊ�ų�����
                for(int i =enemyX+2;i>=enemyX-2;i--){
                    for(int j = enemyY-2;j<=enemyY+2;j++){
                        if(i>=0&&i<=5&&j>=0&&j<=4){
                            if(abs(i-enemyX)>1||abs(j-enemyY)>1){
                                if(nowBoard[i][j] == 0){
                                    finalStep[0] = i;
                                    finalStep[1] = j;
                                }
                            }
                        }
                    }
                }
                if(finalStep[0] == -1){//û���������ܷ���
                    if(enemyStepNum <junqiStepNum ){//ɱ���첽���໹��ɱ�����Ӳ�����
                        for(int i = 0;i<4;i++){
                            finalStep[i] = enemyStep[i];
                        }
                    }else{//ɱ�������
                        for(int i = 0;i<4;i++){
                            finalStep[i] = junqiStep[i];
                        }
                        if(finalStep[2] == -1){//û����ɱ����ľͷ�
                            int latestx,latesty;
                            for(int i=0;i<6;i++){
                                for(int j=0;j<5;j++){
                                    if(nowBoard[i][j]==0){
                                        if((11-i+abs(j-1))<distance){
                                            distance = 11-i+abs(j-1);
                                            latestx=i;
                                            latesty=j;
                                        }
                                    }
                                }
                            }
                            if(latestx != -1){//�ܷ�
                                finalStep[0] = latestx;
                                finalStep[1] = latesty;
                            }else{//����
                                finalStep[0] = -1;
                                finalStep[1] = -1;
                            }
                        }
                    }
                }
            }else{//�ų����µĲ���ȥɱ����
                for(int i = 0;i<4;i++){
                    finalStep[i] = junqiStep[i];
                }
                if(finalStep[2] == -1){//û����ɱ����ľͷ�
                    int latestx,latesty;
                    for(int i=0;i<6;i++){
                        for(int j=0;j<5;j++){
                            if(nowBoard[i][j]==0){
                                if((11-i+abs(j-1))<distance){
                                    distance = 11-i+abs(j-1);
                                    latestx=i;
                                    latesty=j;
                                }
                            }
                        }
                    }
                    if(latestx != -1){//�ܷ�
                        finalStep[0] = latestx;
                        finalStep[1] = latesty;
                    }else{//����
                        finalStep[0] = -1;
                        finalStep[1] = -1;
                    }
                }
            }
        }
    }else{
        int latestx = -1,latesty = -1;
        if(peoplehighestLevel>AIhighestLevel){//�����ߵȼ�����AI
            for(int i=0;i<6;i++){
                for(int j=0;j<5;j++){
                    if(nowBoard[i][j]==0){
                        if((11-i+abs(j-1))<distance){
                            distance = 11-i+abs(j-1);
                            latestx=i;
                            latesty=j;
                        }
                    }
                }
            }
            if(latestx != -1){//�ܷ�
                finalStep[0] = latestx;
                finalStep[1] = latesty;
            }else{//û����
                for(int i = 0;i<4;i++){
                    finalStep[i] = junqiStep[i];
                }
                if(finalStep[2] == -1){
                    finalStep[0] = -1;
                }
            }
        }else{//С�ڵ���
            if(junqiStep[2]!=-1){
                for(int i = 0;i<4;i++){
                    finalStep[i] = junqiStep[i];
                }
            }
            else{//û������������Ҳ��
                for(int i=0;i<6;i++){
                    for(int j=0;j<5;j++){
                        if(nowBoard[i][j]==0){
                            if((11-i+abs(j-1))<distance){
                                distance = 11-i+abs(j-1);
                                latestx=i;
                                latesty=j;
                            }
                        }
                    }
                }
                if(latestx != -1){//�ܷ�
                    finalStep[0] = latestx;
                    finalStep[1] = latesty;
                }else{//û���ı���
                    finalStep[0] = -1;
                    finalStep[1] = -1;
                }
            }
        }
    }
    std::string result = "";
    for(int i = 0; i <4 ;i++){
        result = result + std::to_string(finalStep[i])+",";
    }
    return result;
}

void EasyAI::bfsToTarget(int startX, int startY, int targetX, int targetY, int nowBoard[12][5], int& stepNum, int step[4]) {
    // �˸�����
    int directions[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    // �Ƿ����
    bool visited[12][5];
    memset(visited, false, sizeof(visited));
    // ��¼����
    int distance[12][5];
    memset(distance, -1, sizeof(distance));  // -1 û��
    // ��¼ǰ���ڵ�
    std::pair<int, int> prev[12][5];
    memset(prev, -1, sizeof(prev));  // -1��ʾû��ǰ���ڵ�
    // BFS����
    std::queue<std::pair<int, int>> q;
    q.push({startX, startY});
    visited[startX][startY] = true;
    distance[startX][startY] = 0;
    // ��ʼ�� step ����
    step[0] = startX;
    step[1] = startY;
    bool found = false;
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        // ����ҵ���Ŀ�ֹ꣬ͣ����
        if (x == targetX && y == targetY) {
            found = true;
            break;
        }
        // ������ǰ�ڵ�İ˸�����
        for (int i = 0; i < 8; i++) {
            int nx = x + directions[i][0];
            int ny = y + directions[i][1];

            // �ж��µ�λ���Ƿ�Ϸ���δ�����ʹ�
            if (nx >= 0 && nx < 12 && ny >= 0 && ny < 5 && !visited[nx][ny] && isValidMove(nx, ny, nowBoard, nowBoard[startX][startY], x, y)) {
                visited[nx][ny] = true;
                distance[nx][ny] = distance[x][y] + 1;
                prev[nx][ny] = {x, y};  // ��¼ǰ���ڵ�
                q.push({nx, ny});
            }
        }
                // �����Ծ
        int jumpMax = 9;  // �����Ծ����
        for (int i = 0; i < 4; i++) {
            for (int jump = 2; jump <= jumpMax; jump++) {
                int nx = x + directions[i][0] * jump;
                int ny = y + directions[i][1] * jump;

                // Խ����
                if (nx >= 0 && nx < 12 && ny >= 0 && ny < 5) {
                    // �Ƿ������Ծ���ƶ���Ч
                    if (isValidJumpMove(nx, ny, nowBoard, nowBoard[startX][startY], x, y) && isValidMove(nx, ny, nowBoard, nowBoard[startX][startY], x, y)) {
                        if (!visited[nx][ny]) {
                            visited[nx][ny] = true;
                            distance[nx][ny] = distance[x][y] + 1;
                            prev[nx][ny] = {x, y};  // ��¼ǰ���ڵ�
                            q.push({nx, ny});
                        }
                    } else {
                        break;  // ���������Ծ��ֹͣ��Ծ
                    }
                } else {
                    break;  // Խ�磬ֹͣ��Ծ
                }
            }
        }
    }
    // ����ҵ�Ŀ�꣬�������·��
    if (found) {
        // ��Ŀ��ڵ���ݵ���ʼλ�ã�ֱ��������ʼλ��
        int currX = targetX;
        int currY = targetY;
        std::vector<std::pair<int, int>> path;
        while (currX != startX || currY != startY) {
            path.push_back({currX, currY});
            std::pair<int, int> prevNode = prev[currX][currY];
            currX = prevNode.first;
            currY = prevNode.second;
        }
        // ���·���ĵ�һ���Ǵ���ʼλ�õ�·���ϵĵ�һ��λ��
        if (!path.empty()) {
            step[2] = path.back().first;  // ��һ���� x ����
            step[3] = path.back().second; // ��һ���� y ����
            stepNum = distance[targetX][targetY];  // ���·���ĳ���
        } else {
            stepNum = -1;  // ���û��·�������� -1
        }
    } else {
        stepNum = -1;  // ����Ҳ���·�������� -1
    }
}


// �¸������ܲ����߹���
bool EasyAI::isValidMove(int x, int y, int nowBoard[12][5], int currentLevel, int prevX, int prevY) {
    int target = nowBoard[x][y];  // ��ȡĿ������ϵ�����ֵ
    std::set<std::pair<int, int>> forbiddenSet = {{2,1},{4,1},{7,1},{9,1},{3,2},{8,2},{2,3},{4,3},{7,3},{9,3}};
    if(forbiddenSet.find({x, y}) != forbiddenSet.end()){
        if(target!=13&&target!=26){
            return false;
        }
    }
    if(target>0&&target<13){
        return false;
    }
    if (target == 13 || target == 26 || target == 24 || target == 25) {
        // ���� 3��б���ߵ��ж�
        if (abs(x - prevX) == 1 && abs(y - prevY) == 1) {
            // б���ߣ�x �� y ����ͬʱ�����仯
            if (!(x >= 1 && x <= 5 && prevX>= 1 && prevX <= 5) && !(x >= 6 && x <= 10 && prevX>= 6 && prevX <= 10)) {
                return false;
            }
            if((y==1 || y==3)&&(x==1 ||x==3 ||x==5 ||x==6 ||x==8 ||x==10 )){
                return false;// б���ߵ���Ч��
            }
            if((prevY==1 || prevY==3)&&(prevX==1 ||prevX==3 ||prevX==5 ||prevX==6 ||prevX==8 ||prevX==10 )){
                return false;// б���ߵ���Ч��
            }
        }
        // ���� 4�������ֻ������·����
        if (((x>5&&prevX<=5) || (x<=5&&prevX>5)) && (y == 1|| y == 3)) {
            return false;
        }
    }
    if(target == 0)
    {
        if(x < 6){
            return false;
        }
        if (abs(x - prevX) == 1 && abs(y - prevY) == 1) {
            // б���ߣ�x �� y ����ͬʱ�����仯
            if (!(x >= 1 && x <= 5 && prevX>= 1 && prevX <= 5) && !(x >= 6 && x <= 10 && prevX>= 6 && prevX <= 10)) {
                return false;
            }
            if((y==1 || y==3)&&(x==1 ||x==3 ||x==5 ||x==6 ||x==8 ||x==10 )){
                return false;// б���ߵ���Ч��
            }
            if((prevY==1 || prevY==3)&&(prevX==1 ||prevX==3 ||prevX==5 ||prevX==6 ||prevX==8 ||prevX==10 )){
                return false;// б���ߵ���Ч��
            }
        }
        // ���� 4�������ֻ������·����
        if (((x>5&&prevX<=5) || (x<=5&&prevX>5)) && (y == 1|| y == 3)) {
            return false;
        }
    }
    // ���� 2����ǰ���ӵȼ�����Ŀ�����ӵĵȼ�����Ŀ��������14-22֮��
    if (target >= 14 && target <= 22) {
        if(currentLevel <= target - 13){
            return false;
        }
        if (abs(x - prevX) == 1 && abs(y - prevY) == 1) {
            // б���ߣ�x �� y ����ͬʱ�����仯
            if (!(x >= 1 && x <= 5 && prevX>= 1 && prevX <= 5) && !(x >= 6 && x <= 10 && prevX>= 6 && prevX <= 10)) {
                return false;
            }
            if((y==1 || y==3)&&(x==1 ||x==3 ||x==5 ||x==6 ||x==8 ||x==10 )){
                return false;// б���ߵ���Ч��
            }
            if((prevY==1 || prevY==3)&&(prevX==1 ||prevX==3 ||prevX==5 ||prevX==6 ||prevX==8 ||prevX==10 )){
                return false;// б���ߵ���Ч��
            }
        }
        // ���� 4�������ֻ������·����
        if (((x>5&&prevX<=5) || (x<=5&&prevX>5)) && (y == 1|| y == 3)) {
            return false;
        }
    }
    // ���� 2����ǰ���ӵȼ�С�ڵ���6ʱ��Ŀ��Ϊ23�����ӿ�����
    if (target == 23) {
        if(currentLevel > 6){
            return false;
        }
        if (abs(x - prevX) == 1 && abs(y - prevY) == 1) {
            // б���ߣ�x �� y ����ͬʱ�����仯
            if (!(x >= 1 && x <= 5 && prevX>= 1 && prevX <= 5) && !(x >= 6 && x <= 10 && prevX>= 6 && prevX <= 10)) {
                return false;
            }
            if((y==1 || y==3)&&(x==1 ||x==3 ||x==5 ||x==6 ||x==8 ||x==10 )){
                return false;// б���ߵ���Ч��
            }
            if((prevY==1 || prevY==3)&&(prevX==1 ||prevX==3 ||prevX==5 ||prevX==6 ||prevX==8 ||prevX==10 )){
                return false;// б���ߵ���Ч��
            }
        }
        // ���� 4�������ֻ������·����
        if (((x>5&&prevX<=5) || (x<=5&&prevX>5)) && (y == 1|| y == 3)) {
            return false;
        }
    }
    return true;  // û��Υ�棬����
}

// �ܲ��ܶಽ��
bool EasyAI::isValidJumpMove(int x, int y, int nowBoard[12][5], int currentLevel, int prevX, int prevY) {
    // ���� x=1,5,6,10 ʱ�����Ŀ�� x ���䣬y �����Խ������ӣ�����Ҫȷ���м�ĸ����� 13 �� 26
    if(y != prevY){
        if (x == 1 || x == 5 || x == 6 || x == 10) {
            // ����Ƿ������Խ������ӣ� x���䣬�� y �᷽���ƶ�
            int startY = std::min(prevY, y);
            int endY = std::max(prevY, y);
            // ȷ���м������ 13 �� 26
            for (int i = startY + 1; i < endY; i++) {
            if (nowBoard[x][i] != 13 && nowBoard[x][i] != 26) {
                return false;
                }
            }
            return true;
        }
    }else{
        // ���� y=0,2,4 ʱ�����Ŀ�� y ���䣬x �����Խ������ӣ�����Ҫȷ���м�ĸ����� 13 �� 26
        if ((y == 0 || y == 4) && (x >= 1 && x <= 10 && prevX>= 1 && prevX <= 10) ) {
            // ����Ƿ������Խ������ӣ�x ���䣬�� y �᷽���ƶ�
            int startX = std::min(prevX, x);
            int endX = std::max(prevX, x);
            // ȷ���м������ 13 �� 26
            for (int i = startX + 1; i < endX; i++) {
                if (nowBoard[i][y] != 13 && nowBoard[i][y] != 26) {
                    return false;
                }
            }
            return true;
        }
    }
    return false;  // ���û�з��ϵĹ��򣬷��� false
}
