#include "EasyAI.h"

std::string EasyAI::getNextStep(Board board) {
    // 移动的方向
    int directions[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    std::set<std::pair<int, int>> forbiddenSet = {{2,1},{4,1},{7,1},{9,1},{3,2},{8,2},{2,3},{4,3},{7,3},{9,3}};
    int AIhighestLevel =0;
    int peoplehighestLevel =0;
    int finalStep[4] = {-1,-1,-1,-1};
    std::string status = board.getBoardState();
    int nowBoard[12][5];
    // 使用字符串流来分割字符串
    std::stringstream ss(status);
    char delimiter;
    // 逐个读取数字并存入数组
    for (int i = 0; i < 12; i++) {
        for(int j =0;j<5;j++){
            ss >> nowBoard[i][j];
            ss >> delimiter;  // 跳过逗号
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
     // 计算军旗的最短路径
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
                    junqiStep[0] = step[0]; // 当前棋子位置
                    junqiStep[1] = step[1];
                    junqiStep[2] = step[2]; // 下一步位置
                    junqiStep[3] = step[3];
                }
            }
        }
    }
    //std::cout<<"军旗步数"<<junqiStepNum<<std::endl;
    //for(int i =0;i<4;i++){
    // 	std::cout<<junqiStep[i]<<"  ";
    //}
    // 计算敌人的最短路径
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
                        enemyStep[0] = step[0]; // 当前棋子位置
                        enemyStep[1] = step[1];
                        enemyStep[2] = step[2]; // 下一步位置
                        enemyStep[3] = step[3];
                    }
                }
            }
        }
    }
   // std::cout<<"杀敌步数"<<enemyStepNum<<std::endl;
    //for(int i =0;i<4;i++){
    //	std::cout<<enemyStep[i]<<"  ";
    int distance = 100;
    if(enemyX!=-1){ //对方棋子进入我方棋盘 (除了行营外)
        if(enemyStepNum<=3){//如果杀进入我方阵地的棋子需要3步以下
            if(enemyStepNum <junqiStepNum ){//杀军旗步数多还是杀该棋子步数多
                for(int i = 0;i<4;i++){
                    finalStep[i] = enemyStep[i];
                }
            }else{//杀军旗更快
                for(int i = 0;i<4;i++){
                    finalStep[i] = junqiStep[i];
                }
            }
        }else{//需要4步甚至以上
            if(highestLevel+13 >= 18){//敌人为团长以上
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
                if(finalStep[0] == -1){//没有两格子能翻的
                    if(enemyStepNum <junqiStepNum ){//杀军旗步数多还是杀该棋子步数多
                        for(int i = 0;i<4;i++){
                            finalStep[i] = enemyStep[i];
                        }
                    }else{//杀军旗更快
                        for(int i = 0;i<4;i++){
                            finalStep[i] = junqiStep[i];
                        }
                        if(finalStep[2] == -1){//没有能杀军旗的就翻
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
                            if(latestx != -1){//能翻
                                finalStep[0] = latestx;
                                finalStep[1] = latesty;
                            }else{//报错
                                finalStep[0] = -1;
                                finalStep[1] = -1;
                            }
                        }
                    }
                }
            }else{//团长以下的不管去杀军旗
                for(int i = 0;i<4;i++){
                    finalStep[i] = junqiStep[i];
                }
                if(finalStep[2] == -1){//没有能杀军旗的就翻
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
                    if(latestx != -1){//能翻
                        finalStep[0] = latestx;
                        finalStep[1] = latesty;
                    }else{//报错
                        finalStep[0] = -1;
                        finalStep[1] = -1;
                    }
                }
            }
        }
    }else{
        int latestx = -1,latesty = -1;
        if(peoplehighestLevel>AIhighestLevel){//玩家最高等级高于AI
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
            if(latestx != -1){//能翻
                finalStep[0] = latestx;
                finalStep[1] = latesty;
            }else{//没翻的
                for(int i = 0;i<4;i++){
                    finalStep[i] = junqiStep[i];
                }
                if(finalStep[2] == -1){
                    finalStep[0] = -1;
                }
            }
        }else{//小于等于
            if(junqiStep[2]!=-1){
                for(int i = 0;i<4;i++){
                    finalStep[i] = junqiStep[i];
                }
            }
            else{//没有棋子能走了也翻
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
                if(latestx != -1){//能翻
                    finalStep[0] = latestx;
                    finalStep[1] = latesty;
                }else{//没翻的报错
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
    // 八个方向
    int directions[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    // 是否访问
    bool visited[12][5];
    memset(visited, false, sizeof(visited));
    // 记录步数
    int distance[12][5];
    memset(distance, -1, sizeof(distance));  // -1 没到
    // 记录前驱节点
    std::pair<int, int> prev[12][5];
    memset(prev, -1, sizeof(prev));  // -1表示没有前驱节点
    // BFS队列
    std::queue<std::pair<int, int>> q;
    q.push({startX, startY});
    visited[startX][startY] = true;
    distance[startX][startY] = 0;
    // 初始化 step 数组
    step[0] = startX;
    step[1] = startY;
    bool found = false;
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        // 如果找到了目标，停止搜索
        if (x == targetX && y == targetY) {
            found = true;
            break;
        }
        // 遍历当前节点的八个方向
        for (int i = 0; i < 8; i++) {
            int nx = x + directions[i][0];
            int ny = y + directions[i][1];

            // 判断新的位置是否合法且未被访问过
            if (nx >= 0 && nx < 12 && ny >= 0 && ny < 5 && !visited[nx][ny] && isValidMove(nx, ny, nowBoard, nowBoard[startX][startY], x, y)) {
                visited[nx][ny] = true;
                distance[nx][ny] = distance[x][y] + 1;
                prev[nx][ny] = {x, y};  // 记录前驱节点
                q.push({nx, ny});
            }
        }
                // 多格跳跃
        int jumpMax = 9;  // 最高跳跃步数
        for (int i = 0; i < 4; i++) {
            for (int jump = 2; jump <= jumpMax; jump++) {
                int nx = x + directions[i][0] * jump;
                int ny = y + directions[i][1] * jump;

                // 越界检查
                if (nx >= 0 && nx < 12 && ny >= 0 && ny < 5) {
                    // 是否可以跳跃且移动有效
                    if (isValidJumpMove(nx, ny, nowBoard, nowBoard[startX][startY], x, y) && isValidMove(nx, ny, nowBoard, nowBoard[startX][startY], x, y)) {
                        if (!visited[nx][ny]) {
                            visited[nx][ny] = true;
                            distance[nx][ny] = distance[x][y] + 1;
                            prev[nx][ny] = {x, y};  // 记录前驱节点
                            q.push({nx, ny});
                        }
                    } else {
                        break;  // 如果不能跳跃，停止跳跃
                    }
                } else {
                    break;  // 越界，停止跳跃
                }
            }
        }
    }
    // 如果找到目标，回溯最短路径
    if (found) {
        // 从目标节点回溯到起始位置，直到到达起始位置
        int currX = targetX;
        int currY = targetY;
        std::vector<std::pair<int, int>> path;
        while (currX != startX || currY != startY) {
            path.push_back({currX, currY});
            std::pair<int, int> prevNode = prev[currX][currY];
            currX = prevNode.first;
            currY = prevNode.second;
        }
        // 最短路径的第一步是从起始位置到路径上的第一个位置
        if (!path.empty()) {
            step[2] = path.back().first;  // 第一步的 x 坐标
            step[3] = path.back().second; // 第一步的 y 坐标
            stepNum = distance[targetX][targetY];  // 最短路径的长度
        } else {
            stepNum = -1;  // 如果没有路径，返回 -1
        }
    } else {
        stepNum = -1;  // 如果找不到路径，返回 -1
    }
}


// 下个格子能不能走规则
bool EasyAI::isValidMove(int x, int y, int nowBoard[12][5], int currentLevel, int prevX, int prevY) {
    int target = nowBoard[x][y];  // 获取目标格子上的棋子值
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
        // 规则 3：斜着走的判断
        if (abs(x - prevX) == 1 && abs(y - prevY) == 1) {
            // 斜着走：x 和 y 坐标同时发生变化
            if (!(x >= 1 && x <= 5 && prevX>= 1 && prevX <= 5) && !(x >= 6 && x <= 10 && prevX>= 6 && prevX <= 10)) {
                return false;
            }
            if((y==1 || y==3)&&(x==1 ||x==3 ||x==5 ||x==6 ||x==8 ||x==10 )){
                return false;// 斜着走的有效性
            }
            if((prevY==1 || prevY==3)&&(prevX==1 ||prevX==3 ||prevX==5 ||prevX==6 ||prevX==8 ||prevX==10 )){
                return false;// 斜着走的有效性
            }
        }
        // 规则 4：交界地只有三条路能走
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
            // 斜着走：x 和 y 坐标同时发生变化
            if (!(x >= 1 && x <= 5 && prevX>= 1 && prevX <= 5) && !(x >= 6 && x <= 10 && prevX>= 6 && prevX <= 10)) {
                return false;
            }
            if((y==1 || y==3)&&(x==1 ||x==3 ||x==5 ||x==6 ||x==8 ||x==10 )){
                return false;// 斜着走的有效性
            }
            if((prevY==1 || prevY==3)&&(prevX==1 ||prevX==3 ||prevX==5 ||prevX==6 ||prevX==8 ||prevX==10 )){
                return false;// 斜着走的有效性
            }
        }
        // 规则 4：交界地只有三条路能走
        if (((x>5&&prevX<=5) || (x<=5&&prevX>5)) && (y == 1|| y == 3)) {
            return false;
        }
    }
    // 规则 2：当前棋子等级大于目标棋子的等级，且目标棋子在14-22之间
    if (target >= 14 && target <= 22) {
        if(currentLevel <= target - 13){
            return false;
        }
        if (abs(x - prevX) == 1 && abs(y - prevY) == 1) {
            // 斜着走：x 和 y 坐标同时发生变化
            if (!(x >= 1 && x <= 5 && prevX>= 1 && prevX <= 5) && !(x >= 6 && x <= 10 && prevX>= 6 && prevX <= 10)) {
                return false;
            }
            if((y==1 || y==3)&&(x==1 ||x==3 ||x==5 ||x==6 ||x==8 ||x==10 )){
                return false;// 斜着走的有效性
            }
            if((prevY==1 || prevY==3)&&(prevX==1 ||prevX==3 ||prevX==5 ||prevX==6 ||prevX==8 ||prevX==10 )){
                return false;// 斜着走的有效性
            }
        }
        // 规则 4：交界地只有三条路能走
        if (((x>5&&prevX<=5) || (x<=5&&prevX>5)) && (y == 1|| y == 3)) {
            return false;
        }
    }
    // 规则 2：当前棋子等级小于等于6时，目标为23的棋子可以走
    if (target == 23) {
        if(currentLevel > 6){
            return false;
        }
        if (abs(x - prevX) == 1 && abs(y - prevY) == 1) {
            // 斜着走：x 和 y 坐标同时发生变化
            if (!(x >= 1 && x <= 5 && prevX>= 1 && prevX <= 5) && !(x >= 6 && x <= 10 && prevX>= 6 && prevX <= 10)) {
                return false;
            }
            if((y==1 || y==3)&&(x==1 ||x==3 ||x==5 ||x==6 ||x==8 ||x==10 )){
                return false;// 斜着走的有效性
            }
            if((prevY==1 || prevY==3)&&(prevX==1 ||prevX==3 ||prevX==5 ||prevX==6 ||prevX==8 ||prevX==10 )){
                return false;// 斜着走的有效性
            }
        }
        // 规则 4：交界地只有三条路能走
        if (((x>5&&prevX<=5) || (x<=5&&prevX>5)) && (y == 1|| y == 3)) {
            return false;
        }
    }
    return true;  // 没有违规，能走
}

// 能不能多步走
bool EasyAI::isValidJumpMove(int x, int y, int nowBoard[12][5], int currentLevel, int prevX, int prevY) {
    // 对于 x=1,5,6,10 时，如果目标 x 不变，y 允许跨越多个格子，但需要确保中间的格子是 13 或 26
    if(y != prevY){
        if (x == 1 || x == 5 || x == 6 || x == 10) {
            // 检查是否允许跨越多个格子： x不变，沿 y 轴方向移动
            int startY = std::min(prevY, y);
            int endY = std::max(prevY, y);
            // 确保中间格子是 13 或 26
            for (int i = startY + 1; i < endY; i++) {
            if (nowBoard[x][i] != 13 && nowBoard[x][i] != 26) {
                return false;
                }
            }
            return true;
        }
    }else{
        // 对于 y=0,2,4 时，如果目标 y 不变，x 允许跨越多个格子，但需要确保中间的格子是 13 或 26
        if ((y == 0 || y == 4) && (x >= 1 && x <= 10 && prevX>= 1 && prevX <= 10) ) {
            // 检查是否允许跨越多个格子：x 不变，沿 y 轴方向移动
            int startX = std::min(prevX, x);
            int endX = std::max(prevX, x);
            // 确保中间格子是 13 或 26
            for (int i = startX + 1; i < endX; i++) {
                if (nowBoard[i][y] != 13 && nowBoard[i][y] != 26) {
                    return false;
                }
            }
            return true;
        }
    }
    return false;  // 如果没有符合的规则，返回 false
}
