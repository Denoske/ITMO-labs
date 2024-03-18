package lab1.task2;

import java.util.Collection;
import java.util.LinkedList;
import java.util.Arrays;

abstract class BinarySearchTree<E extends Comparable<E>> implements Tree<E> {
    protected TreeNode<E> root;
    protected int size = 0;
    public BinarySearchTree() {
    }
    public BinarySearchTree(E[] objects) {
        this.addAll(Arrays.asList(objects));
    }

    @Override
    public boolean search(E e) {
        TreeNode<E> current = root; // Start from the root

        while (current != null) {
            if (e.compareTo(current.element) < 0) {
                current = current.left;
            } else if (e.compareTo(current.element) > 0) {
                current = current.right;
            } else // element matches current.element
                return true; // Element is found
        }

        return false;
    }
    public void traversePreOrder(StringBuilder sb, BinaryTreeModel node) {
        if (node != null) {
            sb.append(node.getValue());
            sb.append("\n");
            traversePreOrder(sb, node.getLeft());
            traversePreOrder(sb, node.getRight());
        }
    }



    @Override
    public boolean insert(E e) {
        if (root == null)
            root = createNewNode(e); // Create a new root
        else {
            // Locate the parent node
            TreeNode<E> parent = null;
            TreeNode<E> current = root;
            while (current != null)
                if (e.compareTo(current.element) < 0) {
                    parent = current;
                    current = current.left;
                } else if (e.compareTo(current.element) > 0) {
                    parent = current;
                    current = current.right;
                } else
                    return false; // Duplicate node not inserted
            // Create the new node and attach it to the parent node
            if (e.compareTo(parent.element) < 0)
                parent.left = createNewNode(e);
            else
                parent.right = createNewNode(e);
        }
        size++;
        return true; // Element inserted successfully
    }
    protected TreeNode<E> createNewNode(E e) {
        return new TreeNode<>(e);
    }

    public void getNodeArray(TreeNode<E> root, LinkedList<Integer> list) {

        if (root != null) {
            getNodeArray(root.left, list);
            list.add((Integer) root.element);
            getNodeArray(root.right, list);
        }
    }
    public int[] getArray(){

        LinkedList<Integer> out = new LinkedList<>();

        getNodeArray(root, out);

        return out.stream().mapToInt(i->i).toArray();
    }

    @Override
    public int getSize() {
        return size;
    }

    @Override
    public boolean delete(E e) {
        TreeNode<E> parent = null;
        TreeNode<E> current = root;
        while (current != null) {
            if (e.compareTo(current.element) < 0) {
                parent = current;
                current = current.left;
            } else if (e.compareTo(current.element) > 0) {
                parent = current;
                current = current.right;
            } else
                break;
        }

        if (current == null)
            return false; // Element is not in the tree

        // Case 1: current has no left child
        if (current.left == null) {
            // Connect the parent with the right child of the current node
            if (parent == null) {
                root = current.right;
            } else {
                if (e.compareTo(parent.element) < 0)
                    parent.left = current.right;
                else
                    parent.right = current.right;
            }
        } else {
            // Case 2: The current node has a left child
            // Locate the rightmost node in the left subtree of
            // the current node and also its parent
            TreeNode<E> parentOfRightMost = current;
            TreeNode<E> rightMost = current.left;

            while (rightMost.right != null) {
                parentOfRightMost = rightMost;
                rightMost = rightMost.right; // Keep going to the right
            }

            // Replace the element in current by the element in rightMost
            current.element = rightMost.element;

            // Eliminate rightmost node
            if (parentOfRightMost.right == rightMost)
                parentOfRightMost.right = rightMost.left;
            else
                // Special case: parentOfRightMost == current
                parentOfRightMost.left = rightMost.left;
        }

        size--;
        return true; // Element deleted successfully
    }

    @Override /** Obtain an iterator. Use in order. */
    public java.util.Iterator<E> iterator() {
        return new InorderIterator();
    }
    public class BinaryTreeModel {

        private Object value;
        private BinaryTreeModel left;
        private BinaryTreeModel right;

        public BinaryTreeModel(Object value) {
            this.value = value;
        }

        public Object getValue(){
            return value;
        }
        public BinaryTreeModel getLeft(){
            return left;
        }
        public BinaryTreeModel getRight(){
            return right;
        }

    }

    public String traversePreOrder(TreeNode<E> root) {

        if (root == null) {
            return "";
        }

        StringBuilder sb = new StringBuilder();
        sb.append(root.element);

        String pointerRight = "└──";
        String pointerLeft = (root.right != null) ? "├──" : "└──";

        traverseNodes(sb, "", pointerLeft, root.left, root.right != null);
        traverseNodes(sb, "", pointerRight, root.right, false);

        return sb.toString();
    }
    public void traverseNodes(StringBuilder sb, String padding, String pointer, TreeNode<E> node,
                              boolean hasRightSibling) {
        if (node != null) {
            sb.append("\n");
            sb.append(padding);
            sb.append(pointer);
            sb.append(node.element);

            StringBuilder paddingBuilder = new StringBuilder(padding);
            if (hasRightSibling) {
                paddingBuilder.append("│  ");
            } else {
                paddingBuilder.append("   ");
            }

            String paddingForBoth = paddingBuilder.toString();
            String pointerRight = "└──";
            String pointerLeft = (node.right != null) ? "├──" : "└──";

            traverseNodes(sb, paddingForBoth, pointerLeft, node.left, node.right != null);
            traverseNodes(sb, paddingForBoth, pointerRight, node.right, false);
        }
    }
    public void printNode() {
        System.out.print(traversePreOrder(root));
    }

    // Inner class InorderIterator
    private class InorderIterator implements java.util.Iterator<E> {
        // Store the elements in a list
        private java.util.ArrayList<E> list = new java.util.ArrayList<>();
        private int current = 0; // Point to the current element in list

        public InorderIterator() {
            inorder(); // Traverse binary tree and store elements in list
        }

        /** Inorder traversal from the root */
        private void inorder() {
            inorder(root);
        }

        /** Inorder traversal from a subtree */
        private void inorder(TreeNode<E> root) {
            if (root == null)
                return;
            inorder(root.left);
            list.add(root.element);
            inorder(root.right);
        }
        public boolean hasNext() {
            if (current < list.size())
                return true;

            return false;
        }
        public E next() {
            return list.get(current++);
        }

        public void remove() {
            if (current == 0) // next() has not been called yet
                throw new IllegalStateException();

            delete(list.get(--current));
            list.clear(); // Clear the list
            inorder(); // Rebuild the list
        }
    }
    @Override /** Remove all elements from the tree */
    public void clear() {
        root = null;
        size = 0;
    }
}

interface Tree<E> extends Collection<E> {
    public boolean search(E e);
    public boolean insert(E e);
    public boolean delete(E e);
    public int getSize();
    public default boolean isEmpty() {
        return this.size() == 0;
    }
    public default boolean contains(Object e) {
        return search((E) e);
    }
    public default boolean add(E e) {
        return insert(e);
    }
    public default boolean remove(Object e) {
        return delete((E) e);
    }
    public default int size() {
        return getSize();
    }
    public default <T> T[] toArray(T[] array) {
        return null;
    }
}
class TreeNode<E> {
    public E element;
    public TreeNode<E> left;
    public TreeNode<E> right;
    public TreeNode(E e) {
        element = e;
    }
}