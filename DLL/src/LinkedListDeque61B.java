import java.lang.reflect.Array;
import java.util.LinkedList;
import java.util.ArrayList;
import java.util.List;

public class LinkedListDeque61B<T> implements Deque61B<T> {

    public static void main(String[] args) {
        Deque61B<Integer> lld = new LinkedListDeque61B<>();
        lld.addLast(0);   // [0]
        lld.addLast(1);   // [0, 1]
        lld.addFirst(-1); // [-1, 0, 1]
    }

    private class Node {
        T value;
        Node next;
        Node prev;
        public Node(T value, Node next, Node prev){
            this.value = value;
            this.next = next;
            this.prev = prev;
        }
    }

    private Node dummy;
    private int size;

    public LinkedListDeque61B(){
        this.dummy = new Node(null, null, null);
        this.dummy.next = this.dummy;
        this.dummy.prev = this.dummy;

        this.size = 0;
    }

    /**
     * Add {@code x} to the front of the deque. Assumes {@code x} is never null.
     *
     * @param x item to add
     */
    @Override
    public void addFirst(T x) {
        Node newNode = new Node(x, this.dummy.next, this.dummy);
        this.dummy.next.prev = newNode;
        this.dummy.next = newNode;
        this.size++;
    }

    /**
     * Add {@code x} to the back of the deque. Assumes {@code x} is never null.
     *
     * @param x item to add
     */
    @Override
    public void addLast(T x) {
        Node newNode = new Node(x, this.dummy, this.dummy.prev);
        this.dummy.prev.next = newNode;
        this.dummy.prev = newNode;
        this.size++;
    }

    /**
     * Returns a List copy of the deque. Does not alter the deque.
     *
     * @return a new list copy of the deque.
     */
    @Override
    public List<T> toList() {
        ArrayList<T> toList = new ArrayList<>();

        Node curr = this.dummy.next;
        while(curr != this.dummy){
            toList.add(curr.value);
            curr = curr.next;
        }

        return toList;
    }

    /**
     * Returns if the deque is empty. Does not alter the deque.
     *
     * @return {@code true} if the deque has no elements, {@code false} otherwise.
     */
    @Override
    public boolean isEmpty() {
        if(this.size == 0){
            return true;
        } else {
            return false;
        }
    }

    /**
     * Returns the size of the deque. Does not alter the deque.
     *
     * @return the number of items in the deque.
     */
    @Override
    public int size() {
        return this.size;
    }

    /**
     * Return the element at the front of the deque, if it exists.
     *
     * @return element, otherwise {@code null}.
     */
    @Override
    public T getFirst() {
        return this.dummy.next.value;
    }

    /**
     * Return the element at the back of the deque, if it exists.
     *
     * @return element, otherwise {@code null}.
     */
    @Override
    public T getLast() {
        return this.dummy.prev.value;
    }

    /**
     * Remove and return the element at the front of the deque, if it exists.
     *
     * @return removed element, otherwise {@code null}.
     */
    @Override
    public T removeFirst() {
        if(this.size == 0){
            return null;
        }
        T removed_val = this.dummy.next.value;

        Node newHead = this.dummy.next.next;
        this.dummy.next = newHead;
        newHead.prev = this.dummy;
        this.size--;

        return removed_val;
    }

    /**
     * Remove and return the element at the back of the deque, if it exists.
     *
     * @return removed element, otherwise {@code null}.
     */
    @Override
    public T removeLast() {
        if(this.size == 0){
            return null;
        }
        T valueRemoved = this.dummy.prev.value;

        Node newTail = this.dummy.prev.prev;
        this.dummy.prev = newTail;
        newTail.next = this.dummy;
        this.size--;

        return valueRemoved;
    }

    /**
     * The Deque61B abstract data type does not typically have a get method,
     * but we've included this extra operation to provide you with some
     * extra programming practice. Gets the element, iteratively. Returns
     * null if index is out of bounds. Does not alter the deque.
     *
     * @param index index to get
     * @return element at {@code index} in the deque
     */
    @Override
    public T get(int index) {
        if(index >= this.size || index < 0){
            return null;
        }

        Node curr = this.dummy.next;
        while(index > 0){
            index--;
            curr = curr.next;
        }
        return curr.value;
    }

    /**
     * This method technically shouldn't be in the interface, but it's here
     * to make testing nice. Gets an element, recursively. Returns null if
     * index is out of bounds. Does not alter the deque.
     *
     * @param index index to get
     * @return element at {@code index} in the deque
     */
    @Override
    public T getRecursive(int index) {
        if(index >= this.size || index < 0){
            return null;
        }
        return getRecursiveHelper(index, this.dummy.next);
    }

    private T getRecursiveHelper(int index, Node curr){
        if(index == 0){
            return curr.value;
        }
        return getRecursiveHelper(index - 1, curr.next);
    }


}
