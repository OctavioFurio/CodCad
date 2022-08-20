/*
PROBLEM
https://neps.academy/br/course/estruturas-de-dados-(codcad)/lesson/produto-do-intervalo

TEST CASE
in:
4 6
-2 6 0 -1
C 1 10
P 1 4
C 3 7
P 2 2
C 4 -5
P 1 4
5 9
1 5 -2 4 3
P 1 2
P 1 5
C 4 -5
P 1 5
P 4 5
C 3 0
P 1 5
C 4 -5
C 4 -5
0 0

out:
0+-
+-+-0

*/

#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;

const int MAX_N = 1E5 + 1;              // max n. of leaves
const int H = ceil(log2(MAX_N));    // max height
const int TOTAL = pow(2, H + 1);    // max n. of nodes in tree

int seq[MAX_N]{ 0 };        // array to keep sequence values
short segTree[TOTAL]{ 0 };  // array to represent our tree

// update value of element at index <POS> with <NEW_VALUE> and paths of segment 
// tree
void update(int iNode, int i, int j, int POS, int NEW_VALUE)
{
    if (i == j) // we found the leaf in desired position
    {
        // update element value at given POSition
        seq[POS] = NEW_VALUE;

        // since the question only asks for the sign of the product or zero, we
        // don't need to keep the actual value of the product, so we save only
        // 1, -1 or 0
        segTree[iNode] = NEW_VALUE > 0 ? 1 : (NEW_VALUE < 0 ? -1 : 0);
    }
    else    // keep searching
    {
        int l = 2 * iNode;        // left child
        int r = 2 * iNode + 1;    // right child
        int m = (i + j) / 2;      // divide interval in half

        // choose the subtree that contains the wanted position
        if (POS <= m)
        {
            update(l, i, m, POS, NEW_VALUE);
        }
        else
        {
            update(r, m + 1, j, POS, NEW_VALUE);
        }

        // node value is the product of its children
        segTree[iNode] = segTree[l] * segTree[r];
    }
}

// retrieve the product sign of sequence elements in interval [A, B]
int productSign(int iNode, int i, int j, int A, int B)
{
    // Case 1: [i, j]⊆[A, B] -> return the value of this node
    if (A <= i && j <= B)
    {
        return segTree[iNode];
    }

    // Case 2: [i, j] and [A, B] are disjoint -> return -2 (not found)
    if (j < A || i > B)
    {
        return -2;
    }

    // Case 3: [i, j]∩[A, B]≠∅ but [i, j]⊄[A, B] -> return the product of the
    // children that are contained in [A, B]
    int l = 2 * iNode;        // left child
    int r = 2 * iNode + 1;    // right child
    int m = (i + j) / 2;      // middle of interval

    int prodSignLeft = productSign(l, i, m, A, B);
    int prodSignRight = productSign(r, m + 1, j, A, B);

    if (prodSignRight == -2)    // right subtree isn't contained in [A, B]
    {
        return prodSignLeft;    // so we just return the value of left subtree
    }
    else if (prodSignLeft == -2)    // left subtree isn't contained in [A, B]
    {
        return prodSignRight;   // so we just return the value of right subtree
    }
    else    // the sign of the product of all elements in left and right subtree
    {       // is the sign of the product of left and right children
        return prodSignLeft * prodSignRight;
    }
}

int main() {
    int N, K;
    stringstream result;

    while (cin >> N >> K)   // stop with EOF character
    {
        // populate arrays with input data
        for (int newValue, i = 1; i <= N; i++)
        {
            cin >> newValue;

            // iNode = 1 because we begin in the tree root
            // i = 1 and j = N because we begin with the entire sequence
            // POS = i because it is the index of the sequence element we want
            // to change the value
            update(1, 1, N, i, newValue);
        }

        // operations (query or update)
        for (int i = 0; i < K; i++)
        {
            char choice;
            cin >> choice;

            if (choice == 'C')  // change value
            {
                int index, value;
                cin >> index >> value;

                update(1, 1, N, index, value);
            }
            else    // retrieve product sign of given interval
            {
                int I, J;
                cin >> I >> J;

                // iNode = 1 because we begin in the tree root
                // i = 1 and j = N because we begin with the entire array
                // A = I and B = J because we want the sign of the product of 
                // all elements in the interval [I, J]
                int answer = productSign(1, 1, N, I, J);

                if (answer > 0)
                {
                    result << '+';
                }
                else if (answer < 0)
                {
                    result << '-';
                }
                else
                {
                    result << '0';
                }
            }
        }

        result << '\n';
    }

    cout << result.str();   // print result of this test case
}
