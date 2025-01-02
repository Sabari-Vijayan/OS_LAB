#!/bin/bash

echo -e "Enter your choice\n1. Addition\n2. Subtraction\n3. Multiplication\n4. Division\n5. Modulus\n6. Exit"
read choice

if [ "$choice" -eq 6 ]; then
   echo "Exiting..."
fi

echo "Enter the numbers"
read num1
read num2

if [ "$choice" -eq 1 ]; then
   sum=$((num1 + num2))
   echo "Sum is $sum"
elif [ "$choice" -eq 2 ]; 
then 
   dif=$((num1 - num2))
   echo "Differnece is $dif"
elif [ "$choice" -eq 3 ]; then
   mul=$((num1 * num2))
   echo "Product is $mul"
elif [ "$choice" -eq 4 ]; then
   if [ "$num2" -eq 0 ]; then
      echo "Division by zero is not allowed."
   else
      div=$((num1 / num2))
      echo "Quotient is $div"
   fi
elif [ "$choice" -eq 5 ]; then
   mod=$((num1 % num2))
   echo "Modulus is $mod"
else
   echo "Invalid choice"
fi

