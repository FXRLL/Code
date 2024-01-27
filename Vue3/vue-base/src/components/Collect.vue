<script setup>
// 自定义属性
defineProps({
    isAllChecked: Boolean, // 是否全选
    allMoney: { type: Number, default: 0 }, // 总金额
    allCount: { type: Number, default: 0 } // 总个数
})

// 自定义事件
let emits = defineEmits([
    'changeAllCheckedState' // 改变全选状态的事件
])
</script>

<template>
    <div class="container">
        <!-- 全选 -->
        <label>
            <input 
                    type="checkbox" 
                    :checked="isAllChecked" 
                    @change="emits('changeAllCheckedState', $event.target.checked)">
            全选
        </label>
        <!-- 总金额 -->
        <span>
            合计金额：
            <strong>￥ {{ allMoney }}</strong>
        </span>
        <!-- 结算按钮 -->
        <button>
            结算【 {{ allCount }} 】
        </button>
    </div>
</template>

<style>
.container {
    padding: 20px;
    margin: auto 15px;
    display: flex;
    justify-content: space-between;
    align-items: center;
}

.container input {
    width: 25px;
    height: 25px;
}

.container label {
    display: flex;
    align-items: center;
    width: 70px;
    justify-content: space-between;
}

.container strong {
    color: red;
}

.container button {
    border: none;
    padding: 15px 25px;
    background-color: rgb(50, 140, 192);
    color: white;
    border-radius: 8px;
    box-shadow: 0 0 5px gray;
}
</style>