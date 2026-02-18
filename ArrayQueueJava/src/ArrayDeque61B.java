import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class ArrayDeque61B<T> implements Deque61B<T>{
    T[] arr;
    private int size;
    private int arrayLength;
    private int first;
    private int last;

    public ArrayDeque61B(){
        this.arr = (T[]) new Object[8];
        this.size = 0;
        this.arrayLength = 8;
        this.first = -1;
        this.last = -1;
    }

    void main(){
        ArrayDeque61B<Integer> arraylist = new ArrayDeque61B<>();
        arraylist.addFirst(30);
        arraylist.addFirst(20);
        arraylist.addFirst(10);
        arraylist.addLast(40);
        arraylist.addFirst(0);

        System.out.println("Using iterator:");
        for (Integer num : arraylist) {
            System.out.println(num);
        }

        System.out.println("\nUsing toList:");
        System.out.println(arraylist.toList());

        System.out.println("To String: " + arraylist.toString());
    }

    private void resizeArrayUp(){
        int newArrayLength = this.arrayLength * 2;
        T[] newArray = (T[]) new Object[newArrayLength];
        for(int i = 0; i < this.size; i++){
            int currIndex = (this.first + i) % this.arrayLength;
            newArray[i] = this.arr[currIndex];
        }
        this.arr = newArray;
        this.arrayLength = newArrayLength;
        this.first = 0;
        this.last = this.size - 1;
    }

    /**
     * Add {@code x} to the front of the deque. Assumes {@code x} is never null.
     *
     * @param x item to add
     */
    @Override
    public void addFirst(T x) {
        if(this.size >= this.arrayLength){
            resizeArrayUp();
        }

        if(this.size == 0){
            this.first = 0;
            this.last = 0;
        } else {
            this.first = (this.first - 1 + this.arrayLength) % this.arrayLength;
        }
        this.arr[this.first] = x;
        this.size++;
    }

    /**
     * Add {@code x} to the back of the deque. Assumes {@code x} is never null.
     *
     * @param x item to add
     */
    @Override
    public void addLast(T x) {
        if(this.size >= this.arrayLength){
            resizeArrayUp();
        }

        if(this.size == 0){
            this.first = 0;
            this.last = 0;
        } else {
            this.last = (this.last + 1) % this.arrayLength;
        }
        this.arr[this.last] = x;
        this.size++;
    }

    /**
     * Returns a List copy of the deque. Does not alter the deque.
     *
     * @return a new list copy of the deque.
     */
    @Override
    public List<T> toList() {
        ArrayList<T> list = new ArrayList<>();
        for(int i = 0; i < this.size; i++){
            int indexToAdd = (this.first + i) % this.arrayLength;
            list.add(this.arr[indexToAdd]);
        }
        return list;
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
        if(this.size == 0){
            return null;
        }
        return this.arr[this.first];
    }

    /**
     * Return the element at the back of the deque, if it exists.
     *
     * @return element, otherwise {@code null}.
     */
    @Override
    public T getLast() {
        if(this.size == 0){
            return null;
        }
        return this.arr[this.last];
    }

    private T removeSizeOne(){
        T removedValue = this.arr[this.first];
        this.arr[this.first] = null;
        this.first = -1;
        this.last = -1;
        this.size = 0;
        return removedValue;
    }

    private void resizeArrayDown(){
        int newArrayLength = this.arrayLength / 2;
        T[] newArray = (T[]) new Object[newArrayLength];
        for(int i = 0; i < this.size; i++){
            int curr = (this.first + i) % this.arrayLength;
            newArray[i] = this.arr[curr];
        }
        this.first = 0;
        this.last = this.size - 1;
        this.arrayLength = newArrayLength;
        this.arr = newArray;
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
        else if(this.size == 1){
            return removeSizeOne();
        }

        T removedValue = this.arr[this.first];
        this.arr[this.first] = null;
        this.first = (this.first + 1) % this.arrayLength;
        this.size--;

        if(this.size * 4 <= this.arrayLength && this.arrayLength >= 16){
            resizeArrayDown();
        }

        return removedValue;
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
        else if(this.size == 1){
            return removeSizeOne();
        }

        T removedValue = this.arr[this.last];
        this.arr[this.last] = null;
        this.last = (this.last - 1 + this.arrayLength) % this.arrayLength;
        this.size--;

        if(this.size * 4 <= this.arrayLength && this.arrayLength >= 16){
            resizeArrayDown();
        }

        return removedValue;
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
        int indexToReturn = (this.first + index) % this.arrayLength;
        return this.arr[indexToReturn];
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
        throw new UnsupportedOperationException("No need to implement getRecursive for ArrayDeque61B.");
    }

    @Override
    public String toString(){
        String result = "[";
        for(int i = 0; i < this.size; i++){
            result += this.get(i);
            if(i < this.size - 1){
                result += ", ";
            }
        }
        result += "]";
        return result;
    }

    @Override
    public boolean equals(Object comparedObject){
        if(this == comparedObject){
            return true;
        }
        if(!(comparedObject instanceof Deque61B)){
            return false;
        }

        ArrayDeque61B<?> comparedDeque = (ArrayDeque61B<?>) comparedObject;
        if(comparedDeque.size() != this.size){
            return false;
        }
        for(int i = 0; i < this.size; i++){
            if(!this.get(i).equals(comparedDeque.get(i))){
                return false;
            }
        }
        return true;
    }

    public Iterator<T> iterator(){
        return new ArrayDequeIterator();
    }

    private class ArrayDequeIterator implements Iterator<T> {
        private int pos;

        public ArrayDequeIterator(){
            this.pos = 0;
        }

        @Override
        public boolean hasNext() {
            return this.pos < size;
        }

        @Override
        public T next(){
            T item = get(pos);
            pos++;
            return item;
        }
    }
}
