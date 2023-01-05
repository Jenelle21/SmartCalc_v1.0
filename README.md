Introduction
============

This calculator can:

-   Calculates arbitrary bracket arithmetic expressions in infix
    notation.

-   Calculate expressions in scientific notation - *1e-7, 1e+7*

-   Plotting a function given by an expression in infix notation with
    the variable x.

-   In X, you can also substitute a number.

-   Support the following operands:

    1.  Unary plus *(+2)* and minus *(-2)*;

    2.  Regular plus *(+)* and minus *(-)*;

    3.  Multiplication *(\*)*, division *(/)* and remainder *(mod)*;

    4.  Power *(\^)* and Square Root - *sqrt()*;

    5.  Sinus - *sin()*, Cosinus - *cos()*, Tangens - *tan()*;

    6.  Arcsinus - *asin()*, Arccosinus - *acos()*, Arctangens - *atan()*;

    7.  Decimal logarithm - *log()*, Natural logarithm - *ln()*;

    8.  Brackets - *()* and *X*.

-   Also multiply by bracket - *2(2+2)*;

-   Calculate monthly loan payments, credit term, maximum loan amount
    and total overpayment;

-   Calculate accrued interest on the amount of your deposit, including
    compound interest,
    replenishments and withdrawals;

Installation
============

1.  Download project from repository;

2.  Open terminal and move to project;

3.  Type in terminal: **make install**;

4.  You can find the application on your Desktop or type also **make
    open**.

Usage
=====
- ### Basic:

    1. Open the application from the Desktop;

    2. Enter an expression in the *Input field* or press the buttons below it;

    3. Press **=** or **Enter** key, your answer will instantly appear in *Input field*;

    4. Press **AC** to clear *Input field* or you can press **Del** button to delete only one symbol.

- ### Function graph:

     1. Double click **GrapX** to see the graph of the functions;

     2. Enter the function in the *Input field* and press **GrapX**, your graph will be positioned on the set x-axis;

     3. Press **Back** to move back to the calc.

- ### Credit calculator:
     
    1. Press **Credit** button, then select the calculation and double-click it;

    2. **Monthly payment** allows you to calculate the monthly payment of a credit: 
        * Set the **amount** of credit, then set a **term** in months or years, set the **interest rate** and choose the type - **annuity** or **differential**, finally press **Calculate** and under the white line you will see **a list of monthly payments** for the whole term **in months**, **total overpayment** and **fully paid amount**;

     3. **Credit term** allows you to know the term of the potential loan:
         * Set the **amount** of potentional credit, then set the **monthly payment** you want to pay and the **interest rate**, at the end press **Calculate** and under the white line you will see the **term of loan**, **total overpayment** and **total payout**;
     
     4. **Maximum loan amount** allows you to find out the maximum loan amount depending on the monthly payment:
         * Set the **monthly payment** you want to pay, then specify the **term of the loan** in months or years, set the **interest rate** and finally press **Calculate**, under the white line you will see the **total amount of loan** that you can take, the **total overpayment** and the **total payout**.

- ### Deposit calculator:
    1. Press **Depos** button to open deposit calculator;

    2. Set the **amount** of the potential deposit;
    3. Set the **deposit term**;

    4. Select the **start date of the term**;

    5. Select the **periodicity of payments**;

    6. Select **capitalization**, if necessary;

    7. You can add **Replenishments** and **Withdrawals** from the deposit:
        * Press **Add field** button, then select the **date** of the transaction and its **amount**;

    8. At the end press **Calculate**, you will see the **accrued interest**, the **tax** and the **amount on deposit at the end of the term**.

Uninstallation
==============

1.  Open terminal and move to project;

2.  Type in terminal: **make uninstall**;
