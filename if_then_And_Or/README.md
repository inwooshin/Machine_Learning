# if then And Or

## 목차   
  - [알고리즘](#알고리즘)
  - [결과](#결과)

## 알고리즘   

다음은 if 문을 작성해서 만들어 놓은 뉴런으로 구간을 나누는 것이다.   

![if_then_공식](https://user-images.githubusercontent.com/59462895/126087442-b7215a00-503c-4532-b38a-e8b474f941ab.JPG)   

다음과 같이 x1, x2 의 값을 넣는다. 여기에서

![net공식](https://user-images.githubusercontent.com/59462895/126088438-d50f45e2-f023-4eb1-b78c-6924ac72ccc4.JPG)   

다음의 공식을 사용하였고(net 은 Y와 같다), 2개의 뉴런을 사용하였기 때문에 이를 보기 좋은 수식으로 나타내면   
   
w1 * x1 + w2 * x2 = Y   
   
으로 나타낼 수 있다.   
    
![net값](https://user-images.githubusercontent.com/59462895/126088463-ec08745f-682e-4cb6-9139-dd9e199408ac.JPG)   
   
그리고 위의 연산 w1 * x1 + w2 * x2의 값이 임계값을 넘거나 같으면 Y가 1이되고 그렇지 않을 경우는 0이 되도록 설정하였다.   
   
그리고 이렇게 나온 Y의 값은 기대값과 비교된다. 기대값과 같을 경우에는 w1, w2 의 값을 그대로 둔다. 그러나 그렇지 않을 경우에는 x1 이나 x2의 값이 0이 아니면, w1나 w2의 값을 증가시커거나 감소시켜준다.   
   
위의 기대값과 같아지는 이러한 연산을 100번 수행한다.   

## 결과   
 - OR 연산 수행결과   

![if_then](https://user-images.githubusercontent.com/59462895/126089051-12650662-8fdb-4124-bf11-0a1f12d83118.JPG)   
   
![OR연산](https://user-images.githubusercontent.com/59462895/126089203-d8c78b9c-16cf-47d4-8a9c-c93a3f9812e7.JPG)   
   
여기에서 초기에 설정했던 weight 의 값이 변해서 나왔던 값을 c프로그램에서 받을 수 있고 이 w1, w2 의 값을 파이썬 코드에 넣고 그래프를 그린 결과값이다. 이렇게 나온 결과값이 OR 의 각좌표가 갖는 값과 동일한 것을 알 수 있다.   
   
 - AND 연산 수행결과   

![and](https://user-images.githubusercontent.com/59462895/126090334-31f3fd9f-5ae2-4041-ab87-e2829ddb90dc.JPG)   
   
![AND연산](https://user-images.githubusercontent.com/59462895/126090356-18d15876-db61-484d-aa46-fa5ac7ca5f16.JPG)   
   
위 처럼 연산의 결과가 올바르게 나온 것을 알 수 있다.