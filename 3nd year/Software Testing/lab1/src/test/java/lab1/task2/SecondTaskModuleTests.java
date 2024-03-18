package lab1.task2;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Nested;
import org.junit.jupiter.api.Test;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.util.Collection;
import static org.junit.jupiter.api.Assertions.*;

class SecondTaskModuleTests {
    private final ByteArrayOutputStream outputStreamCaptor = new ByteArrayOutputStream();
    @BeforeEach
    public void setUp() {
        System.setOut(new PrintStream(outputStreamCaptor));
    }


    BinarySearchTree<Integer> tree = new BinarySearchTree<>() {
        @Override
        public Object[] toArray() {
            return new Object[0];
        }

        @Override
        public boolean containsAll(Collection<?> collection) {
            return false;
        }

        @Override
        public boolean addAll(Collection<? extends Integer> collection) {
            return false;
        }

        @Override
        public boolean removeAll(Collection<?> collection) {
            return false;
        }

        @Override
        public boolean retainAll(Collection<?> collection) {
            return false;
        }
    };

    //2d tests

    @Test
    void Insertable(){
        tree = new BinarySearchTree<>() {
            @Override
            public Object[] toArray() {
                return new Object[0];
            }
            @Override
            public boolean containsAll(Collection<?> collection) {
                return false;
            }
            @Override
            public boolean addAll(Collection<? extends Integer> collection) {
                return false;
            }
            @Override
            public boolean removeAll(Collection<?> collection) {
                return false;
            }
            @Override
            public boolean retainAll(Collection<?> collection) {
                return false;
            }
        };
        tree.insert(12);
        assertEquals(tree.getSize(), 1);
        assertArrayEquals(tree.getArray(), new int[]{12});
    }
    @Nested
    public class Insertable{
        @BeforeEach
        void initEach(){
            tree = new BinarySearchTree<>() {
                @Override
                public Object[] toArray() {
                    return new Object[0];
                }

                @Override
                public boolean containsAll(Collection<?> collection) {
                    return false;
                }

                @Override
                public boolean addAll(Collection<? extends Integer> collection) {
                    return false;
                }

                @Override
                public boolean removeAll(Collection<?> collection) {
                    return false;
                }

                @Override
                public boolean retainAll(Collection<?> collection) {
                    return false;
                }
            };
            tree.insert(12);
            tree.insert(8);
            tree.insert(5);
            tree.insert(15);
            tree.insert(7);
        }
        @Test
        void HeapSortedAndGettable(){
            assertArrayEquals(tree.getArray(), new int[]{5, 7, 8, 12, 15});
        }
        @Test
        void SizeCorrect(){
            assertEquals(tree.getSize(), 5);
        }
        @Test
        void PrintTree(){
            tree.printNode();
            assertEquals("12\n" +
                                "├──8\n" +
                                "│  └──5\n" +
                                "│     └──7\n" +
                                "└──15", outputStreamCaptor.toString().trim());
        }
        @Test
        void Clearable(){
            tree.clear();
            assertEquals(tree.getSize(), 0);
            assertArrayEquals(tree.getArray(), new int[]{});
        }
        @Test
        void Deletable(){
            tree.delete(8);
            assertArrayEquals(tree.getArray(), new int[]{5, 7, 12, 15});
        }
        @Test
        void SearchTrue(){
            assertEquals(tree.search(5), true);
        }
        @Test
        void SearchFalse(){
            assertEquals(tree.search(105), false);
        }

    }
}
