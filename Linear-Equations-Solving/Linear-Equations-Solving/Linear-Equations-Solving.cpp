    #include <iostream>
    #include <string>

    using namespace std;

    int main()
    {
        int n;                  // number of equations
        cin >> n;
        cin.ignore();

        // DYNAMIC ALLOCATION
   
        float** coeff = new float* [n];   // coefficients matrix
        for (int i = 0; i < n; i++)
            coeff[i] = new float[n];

        float* rhs = new float[n];       // right hand side
        int vars = 0;                    // number of variables

        // initialize arrays
        for (int i = 0; i < n; i++)
        {
            rhs[i] = 0;
            for (int j = 0; j < n; j++)
                coeff[i][j] = 0;
        }
   
    
     // READ & PARSE EQUATIONS
    
        for (int i = 0; i < n; i++)
        {
            string eq;
            getline(cin, eq);

            float number = 0;
            int sign = 1;
            bool hasNumber = false;
            bool rightSide = false;
            int rhsSign = 1;       // track RHS number sign separately
            int side = 1;          // +1 for LHS, -1 for RHS

            for (int k = 0; k < eq.length(); k++)
            {
                char c = eq[k];

                if (!rightSide)
                {
                    // LHS parsing
                    if (c == '+') sign = 1;
                    else if (c == '-') sign = -1;
                    else if (c >= '0' && c <= '9')
                    {
                        number = number * 10 + (c - '0');
                        hasNumber = true;
                    }
                    else if (c == 'x')
                    {
                        if (!hasNumber) number = 1;

                        k++;
                        int idx = 0;
                        while (k < eq.length() && eq[k] >= '0' && eq[k] <= '9')
                        {
                            idx = idx * 10 + (eq[k] - '0');
                            k++;
                        }
                        k--;

                        coeff[i][idx - 1] += sign * number * side;

                        if (idx > vars) vars = idx;

                        number = 0;
                        hasNumber = false;
                        sign = 1;
                    }
                    else if (c == '=')
                    {
                        rightSide = true;
                        side = -1;       // everything after '=' treated as moved to LHS
                        number = 0;
                        sign = 1;
                    }
                }
                else
                {
                    // RHS parsing (numbers only)
                    if (c == '+') rhsSign = 1;
                    else if (c == '-') rhsSign = -1;
                    else if (c >= '0' && c <= '9')
                    {
                        number = number * 10 + (c - '0');
                    }
                }
            }

            rhs[i] = rhsSign * number;
        }
       
        // COMMAND LOOP
       
        while (true)
        {
            string cmd;
            cin >> cmd;

            if (cmd == "quit")
                break;

            // -------- num_vars --------
            if (cmd == "num_vars")
            {
                cout << vars << endl;
            }

            // -------- equation i --------
            else if (cmd == "equation")
            {
                int id;
                cin >> id;
                id--;

                for (int j = 0; j < vars; j++)
                {
                    if (coeff[id][j] != 0)
                    {
                        if (coeff[id][j] > 0 && j != 0)
                            cout << "+";

                        if (coeff[id][j] != 1)
                            cout << coeff[id][j];

                        cout << "x" << j + 1;
                    }
                }
                cout << "=" << rhs[id] << endl;
            }
            // -------- column xk --------
            else if (cmd == "column")
            {
                string v;
                cin >> v;
                int col = stoi(v.substr(1)) - 1;

                for (int i = 0; i < n; i++)
                    cout << coeff[i][col] << endl;
            }
            // -------- solve (Gaussian Elimination) --------
            else if (cmd == "solve")
            {
                float** a = new float* [n];
                for (int i = 0; i < n; i++)
                    a[i] = new float[vars + 1];

                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < vars; j++)
                        a[i][j] = coeff[i][j];

                    a[i][vars] = rhs[i];
                }

                bool noSolution = false;

                for (int i = 0; i < vars; i++)
                {
                    if (a[i][i] == 0)
                    {
                        for (int k = i + 1; k < n; k++)
                        {
                            if (a[k][i] != 0)
                            {
                                for (int j = 0; j <= vars; j++)
                                {
                                    float temp = a[i][j];
                                    a[i][j] = a[k][j];
                                    a[k][j] = temp;
                                }
                                break;
                            }
                        }
                    }

                    if (a[i][i] == 0)
                    {
                        cout << "No Solution" << endl;
                        noSolution = true;
                        break;
                    }

                    float pivot = a[i][i];
                    for (int j = i; j <= vars; j++)
                        a[i][j] /= pivot;

                    for (int k = 0; k < n; k++)
                    {
                        if (k != i)
                        {
                            float factor = a[k][i];
                            for (int j = i; j <= vars; j++)
                                a[k][j] -= factor * a[i][j];
                        }
                    }
                }

                if (!noSolution)
                {
                    for (int i = 0; i < vars; i++)
                        cout << "x" << i + 1 << "=" << a[i][vars] << endl;
                }

                for (int i = 0; i < n; i++)
                    delete[] a[i];
                delete[] a;
            }
        }
        // FREE MEMORY
        for (int i = 0; i < n; i++)
            delete[] coeff[i];
        delete[] coeff;
        delete[] rhs;

        return 0;
    }