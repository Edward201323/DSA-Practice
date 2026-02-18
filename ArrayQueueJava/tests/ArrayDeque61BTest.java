import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

import java.sql.Array;
import java.util.Deque;

import static com.google.common.truth.Truth.assertThat;

public class ArrayDeque61BTest{

    @Test
    public void add_first_from_empty(){
        Deque61B<Integer> q = new ArrayDeque61B<>();
        q.addFirst(67);

        assertThat(q.toList()).containsExactly(67);
    }

    @Test
    public void add_last_from_empty(){
        Deque61B<Integer> q = new ArrayDeque61B<>();
        q.addLast(69);

        assertThat(q.toList()).containsExactly(69);
    }

    @Test
    public void add_first_nonempty(){
        Deque61B<Integer> q = new ArrayDeque61B<>();
        q.addFirst(420);
        q.addFirst(69);
        q.addFirst(67);

        assertThat(q.toList()).containsExactly(67, 69, 420);
    }

    @Test
    public void add_last_nonempty(){
        Deque61B<Integer> q = new ArrayDeque61B<>();
        q.addLast(67);
        q.addLast(69);
        q.addLast(420);
        assertThat(q.toList()).containsExactly(67, 69, 420);
    }

    @Test
    public void add_first_trigger_resize(){
        Deque61B<Integer> q = new ArrayDeque61B<>();
        q.addFirst(75);
        q.addFirst(74);
        q.addFirst(73);
        q.addFirst(72);
        q.addFirst(71);
        q.addFirst(70);
        q.addFirst(69);
        q.addFirst(68);
        q.addFirst(67);
        assertThat(q.toList()).containsExactly(67, 68, 69, 70, 71, 72, 73, 74, 75);
    }

    @Test
    public void add_last_trigger_resize(){
        Deque61B<Integer> q = new ArrayDeque61B<>();
        q.addLast(67);
        q.addLast(68);
        q.addLast(69);
        q.addLast(70);
        q.addLast(71);
        q.addLast(72);
        q.addLast(73);
        q.addLast(74);
        q.addLast(75);
        assertThat(q.toList()).containsExactly(67, 68, 69, 70, 71, 72, 73, 74, 75);
    }

    @Test
    public void add_first_after_remove_to_empty(){
        Deque61B<Integer> q = new ArrayDeque61B<>();
        q.addFirst(69);
        q.addLast(67);
        q.removeFirst();
        q.removeLast();
        q.addFirst(6967);
        assertThat(q.toList()).containsExactly(6967);
    }

    @Test
    public void add_last_after_remove_to_empty(){
        Deque61B<Integer> q = new ArrayDeque61B<>();
        q.addFirst(69);
        q.addLast(67);
        q.removeFirst();
        q.removeLast();
        q.addLast(6967);
        assertThat(q.toList()).containsExactly(6967);
    }

    @Test
    public void remove_first(){
        ArrayDeque61B<Integer> q = new ArrayDeque61B<>();
        q.addLast(67);
        q.addLast(69);
        q.removeFirst();
        assertThat(q.toList()).containsExactly(69);
    }

    @Test
    public void remove_last(){
        ArrayDeque61B<Integer> q = new ArrayDeque61B<>();
        q.addLast(69);
        q.addFirst(67);
        q.removeLast();
        assertThat(q.toList()).containsExactly(67);
    }

    @Test
    public void remove_first_to_empty(){
        Deque61B<Integer> q = new ArrayDeque61B<>();
        q.addLast(67);
        q.addLast(69);
        q.addLast(420);
        q.removeFirst();
        q.removeFirst();
        q.removeFirst();
        assertThat(q.toList()).isEmpty();
    }

    @Test
    public void remove_last_to_empty(){
        Deque61B<Integer> q = new ArrayDeque61B<>();
        q.addLast(67);
        q.addLast(69);
        q.addLast(420);
        q.removeLast();
        q.removeLast();
        q.removeLast();
        assertThat(q.toList()).isEmpty();
    }

    @Test
    public void remove_first_to_one(){
        Deque61B<Integer> q = new ArrayDeque61B<>();
        q.addLast(67);
        q.addLast(69);
        q.addLast(420);
        q.removeFirst();
        q.removeFirst();
        assertThat(q.toList()).containsExactly(420);
    }

    @Test
    public void remove_last_to_one(){
        Deque61B<Integer> q = new ArrayDeque61B<>();
        q.addLast(67);
        q.addLast(69);
        q.addLast(420);
        q.removeLast();
        q.removeLast();
        assertThat(q.toList()).containsExactly(67);
    }

    @Test
    public void remove_first_trigger_resize(){
        Deque61B<Integer> q = new ArrayDeque61B<>();

        for(int i = 0; i < 16; i++){
            q.addLast(i);
        }

        for(int i = 0; i < 13; i++){
            q.removeFirst();
        }
        assertThat(q.toList()).containsExactly(13, 14, 15);
    }

    @Test
    public void remove_last_trigger_resize(){
        Deque61B<Integer> q = new ArrayDeque61B<>();
        for(int i = 0; i < 16; i++){
            q.addLast(i);
        }

        for(int i = 0; i < 13; i++){
            q.removeLast();
        }
        assertThat(q.toList()).containsExactly(0, 1, 2);
    }

    @Test
    public void get_first_empty(){
        Deque61B<Integer> q = new ArrayDeque61B<>();
        assertThat(q.getFirst()).isNull();
    }

    @Test
    public void get_first_valid(){
        Deque61B<Integer> q = new ArrayDeque61B<>();
        q.addLast(67);
        q.addLast(69);
        assertThat(q.getFirst()).isEqualTo(67);
    }

    @Test
    public void get_last_empty(){
        Deque61B<Integer> q = new ArrayDeque61B<>();
        assertThat(q.getLast()).isNull();
    }

    @Test
    public void get_last_valid(){
        Deque61B<Integer> q = new ArrayDeque61B<>();
        q.addLast(67);
        q.addLast(69);
        assertThat(q.getLast()).isEqualTo(69);
    }

    @Test
    public void get_valid(){
        Deque61B<Integer> q = new ArrayDeque61B<>();
        q.addLast(67);
        q.addLast(69);
        q.addLast(420);
        assertThat(q.get(1)).isEqualTo(69);
    }

    @Test
    public void get_oob_large(){
        Deque61B<Integer> q = new ArrayDeque61B<>();
        q.addLast(67);
        q.addLast(69);
        assertThat(q.get(100)).isNull();
    }

    @Test
    public void get_oob_neg(){
        Deque61B<Integer> q = new ArrayDeque61B<>();
        q.addLast(67);
        q.addLast(69);
        assertThat(q.get(-1)).isNull();
    }

    @Test
    public void size(){
        Deque61B<Integer> q = new ArrayDeque61B<>();
        q.addLast(67);
        q.addLast(69);
        q.addLast(420);
        assertThat(q.size()).isEqualTo(3);
    }

    @Test
    public void size_after_remove_to_empty(){
        Deque61B<Integer> q = new ArrayDeque61B<>();
        q.addLast(67);
        q.addLast(69);
        q.removeFirst();
        q.removeLast();
        assertThat(q.size()).isEqualTo(0);
    }

    @Test
    public void size_after_remove_from_empty(){
        Deque61B<Integer> q = new ArrayDeque61B<>();
        q.removeFirst();
        assertThat(q.size()).isEqualTo(0);
    }

    @Test
    public void is_empty_true(){
        Deque61B<Integer> q = new ArrayDeque61B<>();
        assertThat(q.isEmpty()).isTrue();
    }

    @Test
    public void is_empty_false(){
        Deque61B<Integer> q = new ArrayDeque61B<>();
        q.addLast(67);
        assertThat(q.isEmpty()).isFalse();
    }

    @Test
    public void to_list_empty(){
        Deque61B<Integer> q = new ArrayDeque61B<>();
        assertThat(q.toList()).isEmpty();
    }

    @Test
    public void to_list_nonempty(){
        Deque61B<Integer> q = new ArrayDeque61B<>();
        q.addLast(67);
        q.addLast(69);
        q.addLast(420);
        assertThat(q.toList()).containsExactly(67, 69, 420);
    }

    @Test
    public void resize_up_and_resize_down(){
        Deque61B<Integer> q = new ArrayDeque61B<>();
        for(int i = 0; i < 16; i++){
            q.addLast(i);
        }
        for(int i = 0; i < 13; i++){
            q.removeFirst();
        }
        assertThat(q.toList()).containsExactly(13, 14, 15);
    }
}