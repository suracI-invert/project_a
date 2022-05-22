#include"infotemp.h"

//    posComponent{float x, float y, float offset_center_x, float offset_center_y, float speed}
// -> graphicComponent{std::string id, bool rotate}
// -> collisionComponent{float radius, int boundaryFlag}
// -> behaviorComponent{float x, float y}
// -> muzzleComponent{int flag, int cooldown}  
// -> stateComponent{int hp}

object enemy1_pos1={
    {320, -50, 18, 18}, 
    {"enemy1", false}, 
    {18, 0}, 
    {}, 
    {3, 20}, 
    {10}
};
object enemy1_pos2={
    {640, -50, 18, 18}, 
    {"enemy1", false}, 
    {18, 0}, 
    {}, 
    {3, 20}, 
    {10}
};
object enemy1_pos3={
    {960, -50, 18, 18}, 
    {"enemy1", false}, 
    {18, 0}, 
    {}, 
    {3, 20}, 
    {10}
};
object enemy1_pos4={
    {1330, 240, 18, 18}, 
    {"enemy1", false}, 
    {18, 0}, 
    {}, 
    {3, 20}, 
    {10}
};
object enemy1_pos5={
    {1330, 480, 18, 18}, 
    {"enemy1", false}, 
    {18, 0}, 
    {}, 
    {3, 20}, 
    {10}
};
object enemy1_pos6={
    {320, 770, 18, 18}, 
    {"enemy1", false}, 
    {18, 0}, 
    {}, 
    {3, 20}, 
    {10}
};
object enemy1_pos7={
    {640, 770, 18, 18}, 
    {"enemy1", false}, 
    {18, 0}, 
    {}, 
    {3, 20}, 
    {10}
};
object enemy1_pos8={
    {960, 770, 18, 18}, 
    {"enemy1", false}, 
    {18, 0}, 
    {}, 
    {3, 20}, 
    {10}
};
object enemy1_pos9={
    {-50, 240, 18, 18}, 
    {"enemy1", false}, 
    {18, 0}, 
    {}, 
    {3, 20}, 
    {10}
};
object enemy1_pos10={
    {-50, 480, 18, 18}, 
    {"enemy1", false}, 
    {18, 0}, 
    {}, 
    {3, 20}, 
    {10}
};


object enemy2_pos1={
    {320, -50, 21, 21}, 
    {"enemy2", false}, 
    {18, 0}, 
    {}, 
    {4, 15}, 
    {15}
};
object enemy2_pos2={
    {640, -50, 21, 21}, 
    {"enemy2", false}, 
    {21, 0}, 
    {}, 
    {4, 15}, 
    {15}
};
object enemy2_pos3={
    {960, -50, 21, 21}, 
    {"enemy2", false}, 
    {21, 0}, 
    {}, 
    {4, 15}, 
    {10}
};
object enemy2_pos4={
    {1330, 240, 21, 21}, 
    {"enemy2", false}, 
    {21, 0}, 
    {}, 
    {4, 15}, 
    {15}
};
object enemy2_pos5={
    {1330, 480, 21, 21}, 
    {"enemy2", false}, 
    {21, 0}, 
    {}, 
    {4, 15}, 
    {15}
};
object enemy2_pos6={
    {320, 770, 21, 21}, 
    {"enemy2", false}, 
    {21, 0}, 
    {}, 
    {4, 15}, 
    {15}
};
object enemy2_pos7={
    {640, 770, 21, 21}, 
    {"enemy2", false}, 
    {21, 0}, 
    {}, 
    {4, 15}, 
    {15}
};
object enemy2_pos8={
    {960, 770, 21, 21}, 
    {"enemy2", false}, 
    {21, 0}, 
    {}, 
    {4, 15}, 
    {15}
};
object enemy2_pos9={
    {-50, 240, 21, 21}, 
    {"enemy2", false}, 
    {21, 0}, 
    {}, 
    {4, 15}, 
    {15}
};
object enemy2_pos10={
    {-50, 480, 21, 21}, 
    {"enemy2", false}, 
    {21, 0}, 
    {}, 
    {3, 15}, 
    {10}
};


object enemy3_pos1={
    {640, -50, 21, 21}, 
    {"enemy3", false}, 
    {21, 0}, 
    {}, 
    {8, 15}, 
    {20}
};
object enemy3_pos2={
    {1330, 360, 21, 21}, 
    {"enemy3", false}, 
    {21, 0}, 
    {}, 
    {8, 15}, 
    {20}
};
object enemy3_pos3={
    {640, 770, 21, 21}, 
    {"enemy3", false}, 
    {21, 0}, 
    {}, 
    {8, 15}, 
    {20}
};
object enemy3_pos4={
    {-50, 360, 21, 21}, 
    {"enemy3", false}, 
    {21, 0}, 
    {}, 
    {8, 15}, 
    {20}
};

// object enemy1_list[10]={enemy1_pos1, enemy1_pos2, enemy1_pos3, enemy1_pos4, enemy1_pos5, enemy1_pos6, enemy1_pos7, enemy1_pos8, enemy1_pos9, enemy1_pos10};
// object enemy2_list[10]={enemy2_pos1, enemy2_pos2, enemy2_pos3, enemy2_pos4, enemy2_pos5, enemy2_pos6, enemy2_pos7, enemy2_pos8, enemy2_pos9, enemy2_pos10};
// object enemy3_list[4]={enemy3_pos1, enemy3_pos2, enemy3_pos3, enemy3_pos4};

// wave first={
//     3,
//     {1, 0, 0},
//     {2, 0, 0},
//     {0, 0, 0},
//     {0, 0, 0},
//     {0, 0, 0},
// };
// wave second={
//     6,
//     {2, 0, 0},
//     {4, 0, 0},
//     {0, 0, 0},
//     {0, 0, 0},
//     {0, 0, 0},
// };
// wave third={
//     10,
//     {2, 0, 0},
//     {4, 0, 0},
//     {0, 1, 0},
//     {2, 1, 0},
//     {0, 0, 0},
// };
// wave fourth={
//     15,
//     {4, 0, 0},
//     {6, 0, 0},
//     {2, 2, 0},
//     {0, 0, 1},
//     {0, 0, 0},
// };
// wave fifth={
//     21,
//     {4, 0, 0},
//     {6, 0, 0},
//     {3, 2, 0},
//     {2, 0, 1},
//     {2, 1, 1},
// };