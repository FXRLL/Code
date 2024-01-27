<script setup>
// 声明组件的自定义属性
let propsData = defineProps({
    id: { type: Number, required: true }, // 产品编号
    isChecked: Boolean, // 是否被选中
    picture: { type: String, required: true }, // 图像
    title: { type: String, required: true }, // 标题
    subtitle: { type: String, required: true }, // 副标题
    price: { type: Number, defalut: 0 }, // 单价
    count: { type: Number, defalut: 0 } // 数量
})

// 自定义事件
let emits = defineEmits([
    'changeProductChecked', // 改变复选框的状态事件
    'changeProductCount' // 改变产品数量
])

// 改变产品选中的状态
function changeCheckedState(e) {
    let newCheckedState = e.target.checked // 复选框最新的状态
    emits('changeProductChecked', newCheckedState, propsData.id) // 触发自定义的事件，并传值给父组件
}
</script>

<template>
    <!-- 产品容器 -->
    <div class="box">
        <!-- 选项框 -->
        <input type="checkbox" class="p_checkbox" :checked="isChecked" @change="changeCheckedState">
        <!-- 产品图 -->
        <img class="p_image" :src="picture">
        <!-- 产品内容 -->
        <div class="p_content">
            <!-- 标题 -->
            <h3 class="p_title" v-text="title"></h3>
            <!-- 副标题 -->
            <span class="p_subtitle" v-text="subtitle"></span>
            <!-- 价格 -->
            <h2 class="p_price">￥ {{ price }}</h2>
            <!-- 产品数量区域 -->
            <div class="p_count_area">
                <button :disabled="count <= 1" @click="emits('changeProductCount', -1, id)">-</button>
                <!-- 购买数量 -->
                <span v-text="count"></span>
                <button @click="emits('changeProductCount', 1, id)">+</button>
            </div>
        </div>
    </div>
</template>

<style>
.box {
    box-shadow: 0 0 8px gray;
    padding: 20px;
    margin: 15px;
    display: flex;
    align-items: center;
}

.p_checkbox {
    width: 25px;
    height: 25px;
}

.p_image {
    width: 120px;
    height: 120px;
    margin: 0 20px;
}

.p_content {
    align-self: start;
    position: relative;
    width: 100%;
}

.p_title {
    margin-bottom: 8px;
}

.p_subtitle {
    font-size: 14px;
    color: gray;
}

.p_price {
    margin-top: 20px;
    color: rgb(201, 67, 67);
}

.p_count_area {
    position: absolute;
    bottom: 0;
    right: 0;
}

.p_count_area button {
    width: 25px;
    height: 25px;
}

.p_count_area span {
    margin: 0 10px;
}
</style>