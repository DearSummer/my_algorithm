import java.util.ArrayList;
import java.util.EmptyStackException;

/**
 * 算法:
 *      一个栈,拥有计算自身元素当中最小值的能力
 *      使用了两个栈来实现,第一个栈是栈本身,第二个是辅助,用于存储站当中保存最小值的元素的索引,从而实现了在o(1)时间内获取最小值
 */
public class Main {

    public static void main(String[] args){
        MinStack minStack = new MinStack();

        minStack.push(5);
        minStack.push(5);
        minStack.push(3);
        minStack.push(2);
        minStack.push(7);

        try {
            System.out.println("min value : " + minStack.getMinValue());
            minStack.pop();
            System.out.println("min value : " + minStack.getMinValue());
            minStack.pop();
            System.out.println("min value : " + minStack.getMinValue());
            minStack.pop();
            System.out.println("min value : " + minStack.getMinValue());
            minStack.pop();
            System.out.println("min value : " + minStack.getMinValue());
            minStack.pop();
        }catch (EmptyStackException e){
            System.out.println("stack is empty");
        }

    }
}
