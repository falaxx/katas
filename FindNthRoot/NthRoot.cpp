#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include <ctime>

int GetDoubleSize(double number)
{
    std::string decimalPart = std::to_string(number);
    decimalPart = decimalPart.substr(0,decimalPart.find("."));
    int num = decimalPart.size();
    return num;
}

double GetApprox(double number, int root)
{
    double tmp    = 1.0;
    double approx = number;
    double inf    = std::numeric_limits<double>::infinity();

    //try 2 as a starting point, for big Nth roots
    for (int j = 0; j < root; j++)
    {
        tmp *= 2;
        if (tmp > inf || tmp > number)
            return 1.0; // we know Nth root is between 1 and 2
    }
    while(1)
    {
        tmp = 1.0;
        for (int j = 0; j < root; j++)
        {
            tmp *= approx;
            if (tmp == inf || tmp > number)
            {
                approx /= 10.0;
                break;
            }
        }
        if (tmp <= number)
            break;
    }
    if (approx < 1.0)
        approx = 1.0;
    return approx;
}

double findNthRoot(double number, int root)
{
    double result     = number;
    double tmp        = 0.0;
    double accuracy   = 1.0;
    double tmpResult  = 0.0;
    int    size       = 0;

    if (number == 1.0)
        return 1.0;
    if (root == 1)
        return number;
    if (number < 1.0 || root < 1)
    {
        std::cout << "Invalid input" << std::endl;
        return -1.0;
    }
    result = GetApprox(number, root);
    size = GetDoubleSize(result);

    for (int j = 0; j < size; j++)
        accuracy *= 10;

    while(accuracy > 0.000000000001) // should place accuracy in fonction parameter instead of raw 
    {
        int fixedPointCantCompute = 0;
        while (1)
        {
            if (fixedPointCantCompute == 0)
            {
                tmp = 1.0;
                tmpResult = result + 5*accuracy; //try to take big step
                for (int j = 0; j < root; j++)
                    tmp *= tmpResult;
                if (tmp == number)
                    return result;
                if (tmp < number)
                {
                    result += 5*accuracy;
                    fixedPointCantCompute+=5;
                }
            }
            tmp = 1.0;
            for (int j = 0; j < root; j++)
                tmp *= result;
            if (tmp == number)
                return result;
            if (tmp > number)
            {
                result -= accuracy;
                break;
            }
            result += accuracy;
            fixedPointCantCompute++;
            if (fixedPointCantCompute > 10)
            {
                std::cout << "fixed point issue, cant compute exactly" << std::endl;//program stuck, result will not change anymore
                return result;
            }
        }
        accuracy /= 10.0;
    }
    
    return result;
}

void testNthRoot(double number, int root) // test fonction
{
    double  result   = 0.0;
    double  test     = 1.0;
    int     i        = 0;
    auto    start    = std::chrono::steady_clock::now();

    result = findNthRoot(number, root);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "elapsed time: " << std::fixed << elapsed_seconds.count()*1000 << "ms\n";
    for (int j = 0; j < root; j++)
        test *= result;
    std::string resulttr = std::to_string(test);
    std::string numberStr = std::to_string(number);
    std::cout<< "num in common between number and computed nthroot^root = ";
    while(resulttr[i] || numberStr[i])
    {
        if (resulttr[i] == numberStr[i])
            std::cout <<  resulttr[i];
        else if (resulttr[i] == '.' || numberStr[i] == '.')
            std::cout <<  ".";
        else
            std::cout << "x";
        i++;
    }
    std::cout << std::endl;
    std::cout << "size are equal ? " << std::boolalpha << (GetDoubleSize(test) == GetDoubleSize(number)) <<std::endl;
    std::cout << root << "th root of " << number << "= " << result << std::endl;
    std::cout <<"--------"<< std::endl;
}

int main(){
    
    testNthRoot(4.0, 2);
    testNthRoot(1333.0, 2);
    testNthRoot(1.0, 99999999);
    testNthRoot(9.0, 3);
    testNthRoot(911287361328368761.31276381, 7);
    testNthRoot(91238921323891312763813127638131276381911287361328368761.31276381, 35);
    testNthRoot(312763813127638131276381911287361328368761.31276381, 635);
    testNthRoot(13127638131276381312763819112873613283687612763813127638131276381911287361328368761.31276381, 8635);
    testNthRoot(91238912382763813127631318612763813127638131276381911287361328368761.3819823, 5);

    testNthRoot(99999999.0, 1);
    testNthRoot(3596345248055296.0, 8);
    //88
    testNthRoot(376314121972142913978277049423823770224242354480207001089681468594133184468383517304210471478797375971424967990961273344484255112810274811472054301621808680541948564966423.0, 57);
    //983
    // testNthRoot(939817391287392817321917321982313231928132831313122989139817222223231323132223219281732198372989833928173219837298983392817321983729898312939817391287392817321983729898312939817391287392817321983729898312939817391287392817321983729898312939817391287392817321983729898312939817391287392817321983729898312.0, 141006406);
    // testNthRoot(-32981.319, -9);
}