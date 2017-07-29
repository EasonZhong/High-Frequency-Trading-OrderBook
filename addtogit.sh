clear

echo -e "\n\t Add, Commit, Remote Add and Push to Git initiated ...\n"

read -e -p "Enter the commit comment: " comment
echo $comment

git add .
git commit -m "$comment"
git remote add origin https://github.com/sumantabose/High-Frequency-Trading-OrderBook.git
git push -u origin master

echo -e "\n\t Add, Commit, Remote Add and Push to Git completed ...\n"