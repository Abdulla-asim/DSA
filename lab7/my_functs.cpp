void delete_node(T value) {   
            TreeNode<T> *current_loc, *pred_loc;
            TreeNode<T> *current_prev, *pred_prev;    

            if(!search(value)) return;

            current_loc = location;
            current_prev = prev_location;

            // IF value is at root node
            //if (current_loc && !current_prev) // THINK

            if(is_leaf(current_loc)) {
                delete current_loc;
            }
            else if (only_leftchilds(current_loc)) {
                current_prev->left = current_loc->left;
                delete current_loc;
            }
            else if (only_rightchilds(current_loc)) {
                current_prev->right = current_loc->right;
                delete current_loc;
            }
            else {
                search_predecessor(current_loc);
                // Store Predecessor and its parent locations
                pred_loc = location;
                pred_prev = prev_location;

                if(is_leaf(pred_loc)) {
                    if (current_loc == prev_location->right)
                        current_prev->right = pred_loc;
                    else 
                        current_prev->left = pred_loc;
                    pred_loc->left = current_loc->left;
                    pred_loc->right = current_loc->right;
                    
                    delete current_loc;
                }
                else if ()
            }
            
            location = nullptr;
            prev_location == nullptr;
        }