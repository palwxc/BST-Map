//Programmer: Phillip LaFrance	//Student ID: 12398940
//Intructor: Patrick Taylor		//Section: A		//Date: 04/02/2018
//File: MyMap.hpp			    //Description: Defines functions for MyMap.h


void get_identity(std::string my_id[])
{
    my_id[0]="palwxc";
    my_id[1]="12398940";
}

/**at_helper*/
template <typename K, typename V>
V & MyMap<K, V>::at_helper(TreeNode<MyPair<K, V>> *&rt, const K &key)
{
    //cout << "at_helper Started" << endl;
    if(key < rt->data.first)
        return at_helper(rt->left, key);
    else if(key > rt->data.first)
        return at_helper(rt->right, key);
    else
        return rt->data.second;
        //cout << "\tat_helper Finished from else-statement" << endl;
    //cout << "\tat_helper Finished" << endl;
}

/**size_helper*/
//only use after checking that MyMap is not empty
template <typename K, typename V>
int MyMap<K, V>::size_helper(TreeNode<MyPair<K, V>> *rt) const
{
    int cnt = 1;
    if(rt->right != NULL)
        cnt += size_helper(rt->right);
    if(rt->left != NULL)
        cnt += size_helper(rt->left);
    return cnt;
}

/**clear_helper*/
template <typename K, typename V>
void MyMap<K, V>::clear_helper(TreeNode<MyPair<K, V>> *&rt)
{
    if(rt == NULL)
        return;
    if(rt->left != NULL)
        clear_helper(rt->left);
    if(rt->right != NULL)
        clear_helper(rt->right);
    delete rt;
    rt = NULL;
}

/**insert_helper*/
//inserthelp2 in BST.h (09c)
template <typename K, typename V>
void MyMap<K, V>::insert_helper(TreeNode<MyPair<K, V>> *&rt, const MyPair<K, V> &init_pair)
{
    //cout << "insert_helper Started" << endl;
    if(rt == NULL)
        rt = new TreeNode<MyPair<K, V>>(init_pair, NULL, NULL);
    else if(init_pair.first < rt->data.first)
        insert_helper(rt->left, init_pair);
    else
        insert_helper(rt->right, init_pair);
    //cout << "\tinsert_helper Finished" << endl;
}

/**get_min*/
template <typename K, typename V>
TreeNode<MyPair<K, V>> * MyMap<K, V>::get_min(TreeNode<MyPair<K, V>> *rt)
{
    if(rt->left == NULL)
        return rt;
    else
        return get_min(rt->left);
}

/**erase_helper*/
//removehelp in BST.h (09c)
template <typename K, typename V>
void MyMap<K, V>::erase_helper(TreeNode<MyPair<K, V>> *&rt, const K &key)
{
    if(rt == NULL)
        return;
    else if(key < rt->data.first)
        erase_helper(rt->left, key);
    else if(key > rt->data.first)
        erase_helper(rt->right, key);
    else
    {                                       // Found key
        if(rt->left == NULL)                // Only right child
            rt = rt->right;
        else if(rt->right == NULL)          // Only left child
            rt = rt->left;
        else                                // Both children are present
        {
            TreeNode<MyPair<K, V>> *temp = get_min(rt->right);
            rt->data.second = temp->data.second;
            rt->data.first = temp->data.first;
            erase_helper(rt->right, temp->data.first);
            delete temp;
        }
    }
}

/**find_helper*/
template <typename K, typename V>
MyPair<K, V> * MyMap<K, V>::find_helper(TreeNode<MyPair<K, V>> *rt, const K &key) const
{
    //cout << "find_helper Started" << endl;
    if(rt == NULL)
        return NULL;                        // Empty tree
    if(key < rt->data.first)
        return find_helper(rt->left, key);  // Check left
    else if(key > rt->data.first)
        return find_helper(rt->right, key); // Check right
    else
        return &rt->data;                   // Found key
    //cout << "\tfind_helper Finished \t ERROR" << endl;
}

/**print_helper*/
template <typename K, typename V>
void MyMap<K, V>::print_helper(TreeNode<MyPair<K, V>> *rt, std::string indent) const
{
    if(rt == NULL)                          // Empty tree
    {
        cout << indent << " |=empty" << endl;
        return;
    }
    print_helper(rt->right, indent+="  ");  // Do right subtree
    cout << indent << " " << rt->data.first << " " << rt->data.second << endl;        // Print key and value
    //cout << indent << " " << rt->data.first << endl;        // Print key
    print_helper(rt->left, indent+="");     // Do left subtree
}

/**count_helper*/
template <typename K, typename V>
int MyMap<K, V>::count_helper(TreeNode<MyPair<K, V>> *rt, const K &key) const
{
    int cnt = 0;
    if(rt->data.first == key)
        cnt = 1;
    if(rt->right != NULL)
        cnt += count_helper(rt->right, key);
    if(rt->left != NULL)
        cnt += count_helper(rt->left, key);
    return cnt;
}

/**clone*/
template <typename K, typename V>
TreeNode<MyPair<K, V>> * MyMap<K, V>::clone(const TreeNode<MyPair<K, V>> *rt)
{
    TreeNode<MyPair<K, V>> * copyNode = NULL;
    if (rt != NULL)
    {
        copyNode = new TreeNode<MyPair<K, V>>(rt->data, NULL, NULL);
        copyNode->left = clone(rt->left);
        copyNode->right = clone(rt->right);
    }
    return copyNode;

}


//public//////////////////////////////////////////////////////////////////////

/**Constructor*/
template <typename K, typename V>
MyMap<K, V>::MyMap()
{
    root = NULL;
    //cout << "\tConstructor Finished" << endl;
}

/**Destructor*/
template <typename K, typename V>
MyMap<K, V>::~MyMap()
{
    clear_helper(root);
}

/**Copy constructor*/
template <typename K, typename V>
MyMap<K, V>::MyMap(const MyMap<K, V> &source)
{
    //clear();      //causes core dump in PuTTY
    root = clone(source.root);
    //cout << "\tCopy Constructor Finished" << endl;
}

/**operator=*/
template <typename K, typename V>
MyMap<K, V> & MyMap<K, V>::operator=(const MyMap<K, V> &source)
{
    clear();
    root = clone(source.root);
    return *this;
}

/**at*/
// Should only update, but not insert
// Should throw std::out_of_range exception
template <typename K, typename V>
V & MyMap<K, V>::at(const K &key)
{
    MyPair<K, V> *temp = find_helper(root, key);    // First find it
    if (temp != NULL)
        return at_helper(root, key);                // Key exists
    else
        throw std::out_of_range ("MyMap::at");           // Key does not exist
}

/**operator[]*/
// Updates and inserts
template <typename K, typename V>
V & MyMap<K, V>::operator[](const K &key)
{
    MyPair<K, V> *temp = find_helper(root, key);    // First find key
    if (temp != NULL)
        return at(key);                             // Updates
    else
    {                                               // Inserts
        MyPair<K, V> tmp(key);
        insert(tmp);
        return at(key);
    }
}

/**empty*/
template <typename K, typename V>
bool MyMap<K, V>::empty() const
{
    if(root == NULL)
        return true;
    return false;
}

/**size*/
template <typename K, typename V>
int MyMap<K, V>::size() const
{
    if(empty())
        return 0;
    return size_helper(root);
}

/**clear*/
template <typename K, typename V>
void MyMap<K, V>::clear()
{
    clear_helper(root);
}

/**insert*/
template <typename K, typename V>
void MyMap<K, V>::insert(const MyPair<K, V> &init_pair)
{
    insert_helper(root, init_pair);
}

/**erase*/
// The version that removes by key
template <typename K, typename V>
void MyMap<K, V>::erase(const K &key)
{
    MyPair<K, V> *temp = find_helper(root, key);   // Find Key
    if (temp != NULL)
        erase_helper(root, key);
    //else
        //cout << "ERROR - erase: key not found" << endl;
}

/**find*/
template <typename K, typename V>
MyPair<K, V> * MyMap<K, V>::find(const K &key) const
{
    return find_helper(root, key);
}

/**print*/
template <typename K, typename V>
void MyMap<K, V>::print() const
{
    cout << "\n|||||MapPrintStart|||||" << endl;
    if(empty())
        cout << "   empty" << endl;
    else
        print_helper(root, "");
    cout << "|||||MapPrintStop||||||\n" << endl;
}

/**count*/
template <typename K, typename V>
int MyMap<K, V>::count(const K &key) const
{
    if(empty())
        return 0;
    else
        return count_helper(root, key);
}
