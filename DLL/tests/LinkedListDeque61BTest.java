import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;
import static com.google.common.truth.Truth.assertThat;

public class LinkedListDeque61BTest {

    @Test
    @DisplayName("removeFirst works")
    public void removeFirstTest() {
        Deque61B<Integer> lld = new LinkedListDeque61B<>();
        lld.addLast(1);
        lld.addLast(2);
        lld.addLast(3);
        assertThat(lld.removeFirst()).isEqualTo(1);
        assertThat(lld.toList()).containsExactly(2, 3).inOrder();
    }

    @Test
    @DisplayName("removeLast works")
    public void removeLastTest() {
        Deque61B<Integer> lld = new LinkedListDeque61B<>();
        lld.addLast(1);
        lld.addLast(2);
        lld.addLast(3);
        assertThat(lld.removeLast()).isEqualTo(3);
        assertThat(lld.toList()).containsExactly(1, 2).inOrder();
    }

    @Test
    @DisplayName("removeFirst down to one element")
    public void removeFirstToOne() {
        Deque61B<Integer> lld = new LinkedListDeque61B<>();
        lld.addLast(1);
        lld.addLast(2);
        lld.addLast(3);
        lld.removeFirst();
        lld.removeFirst();
        assertThat(lld.toList()).containsExactly(3).inOrder();
        assertThat(lld.size()).isEqualTo(1);
    }

    @Test
    @DisplayName("removeLast down to one element")
    public void removeLastToOne() {
        Deque61B<Integer> lld = new LinkedListDeque61B<>();
        lld.addLast(1);
        lld.addLast(2);
        lld.addLast(3);
        lld.removeLast();
        lld.removeLast();
        assertThat(lld.toList()).containsExactly(1).inOrder();
        assertThat(lld.size()).isEqualTo(1);
    }

    @Test
    @DisplayName("removeFirst down to empty")
    public void removeFirstToEmpty() {
        Deque61B<Integer> lld = new LinkedListDeque61B<>();
        lld.addLast(1);
        lld.addLast(2);
        lld.removeFirst();
        assertThat(lld.removeFirst()).isEqualTo(2);
        assertThat(lld.toList()).isEmpty();
    }

    @Test
    @DisplayName("removeLast down to empty")
    public void removeLastToEmpty() {
        Deque61B<Integer> lld = new LinkedListDeque61B<>();
        lld.addLast(1);
        lld.addLast(2);
        lld.removeLast();
        assertThat(lld.removeLast()).isEqualTo(1);
        assertThat(lld.toList()).isEmpty();
    }

    @Test
    @DisplayName("removeFirst on empty deque returns null")
    public void removeFirstEmpty() {
        Deque61B<Integer> lld = new LinkedListDeque61B<>();
        assertThat(lld.removeFirst()).isNull();
    }

    @Test
    @DisplayName("removeLast on empty deque returns null")
    public void removeLastEmpty() {
        Deque61B<Integer> lld = new LinkedListDeque61B<>();
        assertThat(lld.removeLast()).isNull();
    }

    @Test
    @DisplayName("addFirst after removing to empty")
    public void addFirstAfterRemoveToEmpty() {
        Deque61B<Integer> lld = new LinkedListDeque61B<>();
        lld.addLast(1);
        lld.addLast(2);
        lld.removeFirst();
        lld.removeFirst();
        lld.addFirst(3);
        assertThat(lld.toList()).containsExactly(3).inOrder();
    }

    @Test
    @DisplayName("addLast after removing to empty")
    public void addLastAfterRemoveToEmpty() {
        Deque61B<Integer> lld = new LinkedListDeque61B<>();
        lld.addLast(1);
        lld.addLast(2);
        lld.removeFirst();
        lld.removeFirst();
        lld.addLast(3);
        assertThat(lld.toList()).containsExactly(3).inOrder();
    }

    @Test
    @DisplayName("size after removing to empty")
    public void sizeAfterRemoveToEmpty() {
        Deque61B<Integer> lld = new LinkedListDeque61B<>();
        lld.addLast(1);
        lld.addLast(2);
        lld.removeFirst();
        lld.removeLast();
        assertThat(lld.size()).isEqualTo(0);
    }

    @Test
    @DisplayName("size after removing from empty")
    public void sizeAfterRemoveFromEmpty() {
        Deque61B<Integer> lld = new LinkedListDeque61B<>();
        lld.removeFirst();
        assertThat(lld.size()).isEqualTo(0);
    }

}