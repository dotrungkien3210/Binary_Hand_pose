#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

static int countDequy = 0;
static int maxHeight = 0;

/// <summary>
/// 
/// </summary>
/// phần 1 tạo tọa độ x y z và id của mỗi khớp
struct handJoint {
    float x;
    float y;
    float z;
    int joints;
    int jointID;//biểu thị các khớp tay

};

// phần 2 tạo struct handPose 
struct handPose {
    handJoint handID;// mỗi id biểu thị tại một thời gian trạng thái bàn tay sẽ như thế nào
    handJoint allJoints[21];
};

// phần 6 tạo struct để kiểm soát lưu lại giá trị ID khi đang short
struct shortArrayID {
    int arraID;
    int countShort;
};

/// <summary>
/// phần 7 tạo cây nhị phân tìm kiếm
/// </summary>

struct node {
    handJoint data; //dữ liệu node có thể kiểu int, float, sinhvien.....
    struct node* pleft;   // node bên phải củaa cây(cây con phải)
    struct node* pright;  // node bên trái củaa cây(cây con trái)
};
typedef struct node NODE;
typedef NODE* TREE;

void khoitaocay(TREE& t)
{
    // tại sao lại có &: khi tạo cái list muốn lưu lại sự khởi tạo đó
    t = NULL;// cây rỗng
}
/// <summary>
/// PreOrder: Node -> Left -> Right
///InOrder: Left->Node->Right
///PostOrder : Left->Right->Node
/// </summary>
/// <param name="t"></param>
void duyetNLR(TREE t) {
    if (t != NULL)
    {
        cout << t->data.joints << " ";// dữ liệu trong node
        duyetNLR(t->pleft);
        duyetNLR(t->pright);
    }
}

void duyetLNR(TREE t) {
    if (t != NULL)
    {
        duyetLNR(t->pleft);
        cout << t->data.joints << " ";// dữ liệu trong node
        duyetLNR(t->pright);
    }
}

void duyetLRN(TREE t) {
    if (t != NULL)
    {
        duyetLRN(t->pleft);
        duyetLRN(t->pright);
        cout << t->data.joints << " ";// dữ liệu trong node
    }
}

void themNodeVaoCay(TREE& t, int x) {
    // phần tử x là số nguyên khai báo trong struct node nên int x là kiểu số nguyên thêm vào
    // nếu cây rỗng thì phần tử đó chính là node gốc (root)
    if (t == NULL) {
        NODE* p = new NODE; // khởi tạo một cái node để thêm vào cây
        p->data.joints = x;// thêm dữ liệu x vào data
        p->pleft = NULL;
        p->pright = NULL;
        t = p;// node p chính là node gốc <=> x chính là node gốc
    }
    else// cây có tồn tại phần tử
    {
        int nhanhCay = 0;// nhánh cây phụ thuộc giá trị x trong khoảng nào nên bỏ trong này được
        if (x >= 1 && x < 5)
        {
            nhanhCay = 1;
        }
        else if (x >= 5 && x < 9)
        {
            nhanhCay = 2;
        }
        else if (x >= 9 && x < 13)
        {
            nhanhCay = 3;
        }
        else if (x >= 13 && x < 17)
        {
            nhanhCay = 4;
        }
        else
        {
            nhanhCay = 5;
        }
        // phần tử thêm vào nhỏ hơn gốc thì đệ quy qua trái
        if (countDequy < nhanhCay)
        {
            countDequy++;
            themNodeVaoCay(t->pright, x);
        }
        else
        {
            // phần tử thêm vào lớn hơn gốc thì đệ quy qua phải
            themNodeVaoCay(t->pleft, x);
        }
    }

}
/* câu 10 : Write a function that determines longest path of the tree.
The function returns to the array storing the ID of node belonging to the longest path. 
*/ 
int maxDepth(TREE t)
{
    if (t == NULL)
        return 0;
    else
    {
        
        int rDepth = maxDepth(t->pright);
        int lDepth = maxDepth(t->pleft);
       
        if (lDepth < rDepth){
            return(lDepth + 1);
        }
        else {
        return(rDepth + 1);
        }
    }
}

void Menu(TREE& t) {
    while (true)
    {
        countDequy = 0;
        system("cls");
        cout << "\n----------------- MENU-----------------------";
        cout << "\n1 nhap du lieu";
        cout << "\n2 Duyet cay theo PreOrder: Node -> Left -> Right";
        cout << "\n3 Duyet cay theo InOrder: Left -> Node -> Right";
        cout << "\n4 Duyet cay theo PostOrder: Left -> Right -> Node";
        cout << "\n5 Height of tree";
        cout << "\n-----------------------------------------------";
        int luachon;
        cout << "\n nhap lua chon: ";
        cin >> luachon;
        if (luachon < 0 || luachon > 5)
        {
            cout << "\nkhong co lua chon hop le";
            system("pause");
        }
        else if (luachon == 1) {
            int x;
            cout << "\nnhap so nguyen x";
            cin >> x;
            themNodeVaoCay(t, x);
        }
        else if (luachon == 2) {
            cout << "Duyet cay theo PreOrder: Node -> Left -> Right";
            duyetNLR(t);
            system("pause");
        }
        else if (luachon == 3) {
            cout << "Duyet cay theo InOrder: Left -> Node -> Right";
            duyetLNR(t);
            system("pause");
        }
        else if (luachon == 4) {
            cout << "Duyet cay theo PostOrder: Left -> Right -> Node";
            duyetLRN(t);
            system("pause");
        }
        else if (luachon == 5) {
            cout << "Height of tree is : ";
            maxDepth(t);
            system("pause");
        }
        else {
            break;
        }
    }
}

int arrayofjoints()
{
    int count = 0;
    int arr[21][21];
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            arr[i][j] = 0;
        }
    }
    arr[0][1] = 1;
    arr[1][0] = 1;
    arr[2][1] = 1;
    arr[1][2] = 1;
    arr[3][2] = 1;
    arr[2][3] = 1;
    arr[3][4] = 1;
    arr[4][3] = 1;
    arr[0][5] = 1;
    arr[5][0] = 1;
    arr[6][5] = 1;
    arr[5][6] = 1;
    arr[0][9] = 1;
    arr[9][0] = 1;
    arr[6][7] = 1;
    arr[7][6] = 1;
    arr[7][8] = 1;
    arr[8][7] = 1;
    arr[9][10] = 1;
    arr[10][9] = 1;
    arr[10][11] = 1;
    arr[11][10] = 1;
    arr[12][11] = 1;
    arr[11][12] = 1;
    arr[13][14] = 1;
    arr[14][13] = 1;
    arr[14][15] = 1;
    arr[15][14] = 1;
    arr[15][16] = 1;
    arr[16][15] = 1;
    arr[0][13] = 1;
    arr[13][0] = 1;
    arr[17][0] = 1;
    arr[0][17] = 1;
    arr[17][18] = 1;
    arr[18][17] = 1;
    arr[18][19] = 1;
    arr[19][18] = 1;
    arr[19][20] = 1;
    arr[20][19] = 1;
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            cout<<arr[i][j];
        }
        cout << "\n";
    }
    return count;
}
/////////////////////// phần 3 đọc file và ghi ra///////////////////
float* readData(float* grades) {


    string inFileName = "btl.txt";
    ifstream inFile;
    inFile.open(inFileName.c_str());

    if (inFile.is_open())
    {
        for (int i = 0; i < 192; i++)
        {
            inFile >> grades[i];

        }

        inFile.close(); // CLose input file
    }
    else { //Error message
        cerr << "Can't find input file " << inFileName << endl;
    }
    return grades;
}
// tính toán tất cả các giá trị giữa các khớp 
// bài 4 array 21x21 tính toán tất cả các giá trị
void calcEuclidianJoints(float arrtwoD[21][3])
{
    handPose handOne;
    for (int j = 0; j < 21; j++)
    {
        handOne.allJoints[j].x = arrtwoD[j][0];
        handOne.allJoints[j].y = arrtwoD[j][1];
        handOne.allJoints[j].z = arrtwoD[j][2];
    }
    float alldistance[21][21];
    for (int i = 0; i < 21; i++) 
    {
        for (int j = 0; j < 21; j++)
        {
            int x = pow(handOne.allJoints[i].x - handOne.allJoints[j].x,2);
            int y = pow(handOne.allJoints[i].y - handOne.allJoints[j].y, 2);
            int z = pow(handOne.allJoints[i].z - handOne.allJoints[j].z, 2);
            alldistance[i][j] = sqrt(x + y + z);
        }
    }
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            cout << alldistance[i][j] << " ";
        }
        cout << "\n";
    }
}
//// bài 5 tính khoảng cách giữa cách khớp trong các thời gian khác nhau
float* calcEuclidianTime(float arrtwoD1[21][3], float arrtwoD2[21][3])
{
    handPose handTime;
    float* distance = new float[21];
    for (int j = 0; j < 21; j++)
    {
        handTime.allJoints[j].x = arrtwoD1[j][0]- arrtwoD2[j][0];
        int x2 = pow(handTime.allJoints[j].x, 2);
        handTime.allJoints[j].y = arrtwoD1[j][1]- arrtwoD2[j][1];
        int y2 = pow(handTime.allJoints[j].y, 2);
        handTime.allJoints[j].z = arrtwoD1[j][2]- arrtwoD2[j][2];
        int z2 = pow(handTime.allJoints[j].z, 2);
        distance[j] = sqrt(x2 + y2 + z2);
    }
   /* for (int j = 0; j < 21; j++)
    {
        cout << distance[j] << "\n";
    }*/
    return distance;

}

int main()
{
    
    float grade[192];

    float* grades = readData(grade);
    //////////////////////////////////////////////////////////////////
    float arrayTam1[64];
    for (int i = 0; i < 64; i++)
    {
        if (i != 0) {
            arrayTam1[i - 1] = grade[i];
        }
    }
    float arrtwoD1[21][3];
    for (int i = 0; i < 64; i++)
    {
        int j = i / 3;
        int k = i % 3;
        arrtwoD1[j][k] = arrayTam1[i];
    }
    ////////////////////////////////////////////////////////////////////
    float arrayTam2[64];
    for (int i = 0; i < 64; i++)
    {
        if (i != 0) {
            arrayTam2[i - 1] = grade[i + 64];
        }
    }
    float arrtwoD2[21][3];
    for (int i = 0; i < 64; i++)
    {
        int j = i / 3;
        int k = i % 3;
        arrtwoD2[j][k] = arrayTam2[i];
    }
    ////////////////////////////////////////////////////////////////////////
    float arrayTam3[64];
    for (int i = 0; i < 64; i++)
    {
        if (i != 0) {
            arrayTam3[i - 1] = grade[i + 128];
        }
    }
    float arrtwoD3[21][3];
    for (int i = 0; i < 64; i++)
    {
        int j = i / 3;
        int k = i % 3;
        arrtwoD3[j][k] = arrayTam3[i];
    }
    // hiển thị khớp nối
    //int kq = arrayofjoints();

    ///////////////////////////////////////////////////////////////////////////
    // bài 4 tính khoảng cách tất cả lưu vào array 21x21
    /* cout << "\nthe distance between two joints is\n";
     calcEuclidianJoints(arrtwoD1);*/
    //////////////////////////////////////////////////////////////////////////
    // bài 5 tính khoảng cách giữa cách khớp trong các thời gian khác nhau
    /*cout << "\nthe distance of one joints between two times is\n";
    float* kq = new float[21];
       kq= calcEuclidianTime(arrtwoD1,arrtwoD2);
       for (int i = 0; i < 21; i++)
       {
           cout << *(kq+i) << "\n";
       }*/
      /*bài 6
      ý tưởng là ta sẽ tạo một struct gồm ID của khớp và số lần khớp đó bị sort
      như vậy ở struct ở bài 6 này ta bắt buộc tạo ra 21 đối tượng theo dõi 21 khớp
      bài này ý tưởng là sẽ tạo ra 3 array 
      có 2 array không đổi là arrayGoc là lưu giá trị trả về từ phần 5 từ đó kiểm soát giá trị thay đổi
      ngoài ra còn array đếm để kiếm soát nếu mà đổi thì ta sẽ tăng giá trị biến đếm tại đó
      1 array thay đổi là arrayTam thực hiện swap theo giải thuật mình chọn
       ở đây em chọn interchange sort, sau mỗi lần swap  thì giá trị nào đã được swap
      từ đó lấy giá trị đó vứt vào vòng for của arrayGoc, thấy giá trị bị đổi đó trùng với 
      giá trị nào trong array gốc thì ta sẽ lấy vị trí index 
      rồi nhảy tiếp vào arraySaveCount tìm giá trị index đó và tăng biến lên +1
      */
     /*
       float arrayTam[21];
       float arraySaveCount[21];// mảng 21 giá trị 0 để đếm phần tử
       float arrayGoc[21];
       for (int i = 0; i < 21; i++)
       {
           arraySaveCount[i] = 0;
       }
       for (int i = 0; i < 21; i++)
       {
           arrayTam[i] = kq[i];
       }
       for (int i = 0; i < 21; i++)
       {
           arrayGoc[i] = kq[i];
       }
           for (int i = 0; i <= 19; i++) // phần tử i cuối cùng đã được sắp xếp
           {
               for (int j = i+1; j <= 20; j++)
               {
                   if (arrayTam[i] > arrayTam[j])
                   {
                       float temp = arrayTam[i];
                       arrayTam[i] = arrayTam[j];
                       arrayTam[j] = temp;
                       for (int k = 0; k < 21; k++)
                       {
                           if (arrayGoc[k] == arrayTam[i])
                           {
                               arraySaveCount[k]++;
                           }
                       }
                       for (int h = 0; h < 21; h++)
                       {
                           if (arrayGoc[h] == arrayTam[j])
                           {
                               arraySaveCount[h]++;
                           }
                       }
                   }
               }
           }
           for (int i = 0; i < 21; i++)
           {
               cout << " the value: " << arrayTam[i] << "\t";
               cout <<" swap times :" << arraySaveCount[i] << "\n";
           }
           int moveTheMost = 0;
           for (int i = 0; i < 21; i++)
           {
               if (arraySaveCount[i] > moveTheMost)
               {
                   moveTheMost = i;
               }
           }
           cout << "\n ID of the joint that moves the most is: " << moveTheMost;
    */
    ////////////////////////////////////////////////////////////////////////
    /// câu 789 khởi tạo cây và thêm vào đều nằm trong phần này
    /// Câu 10 : tìm quãng đường xa nhất so với node gốc
    /*TREE t;
    khoitaocay(t);
    Menu(t);*/
    ///////////////////////////////////////////////////////////////
    return 0;
}