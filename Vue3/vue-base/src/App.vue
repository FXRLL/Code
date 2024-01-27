<script setup>
import { computed, ref } from 'vue';

// 引入产品组件
import ProductVue from './components/Product.vue'
// 引入汇总组件
import CollectVue from './components/Collect.vue'

// 购物车
let shopCar = ref([
    {
        id: 89,
        title: '四川爱媛38号果冻橙 当季时令应季彩箱装甜桔橘子新鲜水果专区 净重2斤小果尝鲜装(力荐大果，口感更好更实惠)',
        subtitle: '由初逐旗舰店从 四川眉山市 发货, 并提供售后服务. 现在至明日17:00前完成下单，预计11月15日19:30前发货',
        image: 'https://img12.360buyimg.com/n1/jfs/t1/39198/22/19565/188868/634a3bc4Ea15f2eee/2bb232b36cdd285c.jpg',
        price: 10,
        count: 1,
        selected: false
    },
    {
        id: 102,
        title: '【现货速发】新鲜四季青柠檬 无籽香水柠檬当季生鲜小青柠檬奶茶店水果 有籽青柠檬1斤装试吃【50-80克】',
        subtitle: '由朵艾美水果旗舰店发货, 并提供售后服务. 现在至明日16:00前完成下单，预计11月16日23:30前发货',
        image: 'https://img12.360buyimg.com/n1/jfs/t1/191077/5/6346/108268/60beea0dEc3a6d2ad/15db7dd619a0bc4f.jpg',
        price: 9,
        count: 3,
        selected: true
    },
    {
        id: 108,
        title: '新疆阿克苏冰糖心苹果 新鲜时令水果 阿克苏苹果红富士 10斤礼盒装 单果75-85mm 净重9斤多',
        subtitle: '由阿克苏苹果旗舰店发货, 并提供售后服务. 现在至明日16:00前完成下单，预计11月16日20:30前发货',
        image: 'https://img13.360buyimg.com/n1/jfs/t1/64647/33/22918/106322/6360afb1E9bab1003/a82bda0aeae6e953.png',
        price: 80,
        count: 2,
        selected: false
    }
])

// 产品的状态发生改变
function changeShopCarProductChecked(checked, id) {
    // 循环购物车中的每个产品
    shopCar.value.some(product => {
        // 判断更改的是哪一个产品的 checked 状态
        if (id === product.id) {
            product.selected = checked // 改变购物车中指定产品的选中的值
            return true // 结束循环
        }
    })
}

// 产品数量更改
function changeShopCarProductCount(count, id){
    // 循环购物车中的每个产品
    shopCar.value.some(product => {
        // 判断更改的是哪一个产品的 checked 状态
        if (id === product.id) {
            product.count += count // 改变购物车中指定产品的数量
            return true // 结束循环
        }
    })
}


// 是否全选购物车产品
let isFullSelecteProduct = computed(()=>{
    return shopCar.value.every(product => product.selected)
})

// 改变购物车所有产品的选中状态
function changeShopCarAllProductCheckedState(checked){
    shopCar.value.forEach(product => product.selected = checked )
}

// 总金额
let total = computed(() => {
    return shopCar.value
    .filter(item => item.selected) // 过滤掉被选中得产品
    .reduce((money, item) => (money += item.price * item.count ), 0) // 累加器
}) 


// 购买总数量
let countSum = computed(() => {
    return shopCar.value
    .filter(item => item.selected) // 过滤掉被选中得产品
    .reduce((count, item) => (count += item.count ), 0) // 累加器
})
</script>

<template>
    <!-- 产品组件 -->
    <ProductVue 
                v-for="product in shopCar" 
                :key="product.id" 
                :id="product.id" 
                :picture="product.image"
                :title="product.title"
                :subtitle="product.subtitle"
                :price="product.price"
                :count="product.count"
                :is-checked="product.selected"
                @change-product-checked="changeShopCarProductChecked" 
                @change-product-count="changeShopCarProductCount"
    />

    <hr>

    <!-- 使用汇总组件 -->
    <CollectVue 
                :is-all-checked="isFullSelecteProduct"
                :all-money="total"
                :all-count="countSum"
                @change-all-checked-state="changeShopCarAllProductCheckedState"
    />
</template>

<style>
* {
    margin: 0;
    padding: 0;
}
</style>