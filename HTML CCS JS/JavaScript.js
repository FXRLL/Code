//如果放在HTML文件中，<script>最好放在</body>后面
if (false) {
    console.log("switch 1");
}
else if (false) {
    console.log("switch 2");
}
else {
    console.log("switch 3");
}
for (var i = 0; i < 5; i++) {
    console.log(i);
}
var i = 0;
while (i < 5) {
    console.log(i);
    i = i + 1;
}
//函数声明语句
//有函数名提升效果
function test1() {
    console.log("Success！");
}
test1();
//函数定义表达式
var test2 = function () {
    console.log("Success！");
}
test2();
//对象的创建
var obj1 =
{
    name: "TJUT",
    hello: function () {
        console.log("Hello Success！");
    },
    cats: ["A", "B", "C", 4],//数组
    dog: {
        name: "孟祥瑞",
        age: 20,
    }
}
console.log(obj1);
obj1.hello();
var str = JSON.stringify(obj1);
var obj2 = JSON.parse(str);