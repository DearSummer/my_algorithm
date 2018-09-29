import java.util.ArrayList;
import java.util.EmptyStackException;
import java.util.List;

public class MinStack  {

    private List<Integer> stackList = new ArrayList<>();
    private List<Integer> minIndexList = new ArrayList<>();

    public Integer pop(){
        if(stackList.size() == 0){
            throw new EmptyStackException();
        }

        //获取栈顶元素,若这个元素就是最小值所在的索引,则去除这个元素,从最小值列表当中
        Integer value = stackList.get(stackList.size() - 1);
        if((stackList.size() - 1) == minIndexList.get(minIndexList.size() - 1)){
            minIndexList.remove(minIndexList.size() - 1);
        }

        stackList.remove(stackList.size() - 1);
        return value;
    }

    public void push(Integer value){

        stackList.add(value);

        //若此时为第一个元素,则将这个元素设为栈最小值
        //否则查找栈最小值,若新的元素的值更小,则将新的元素的索引加入到对最小值的索引的列表当中
        if(minIndexList.size() == 0){
            minIndexList.add(0);
        }else{
            Integer minValue = getMinValue();
            if(minValue > value){
                minIndexList.add(stackList.size() - 1);
            }
        }

    }

    public Integer getMinValue(){
        if(stackList.size() == 0){
            throw new EmptyStackException();
        }
        return stackList.get(minIndexList.get(minIndexList.size() - 1));

    }
}
