// .vitepress/theme/index.ts
import { h } from 'vue'
import DefaultTheme from 'vitepress/theme'
import HashCalculator from './components/HashCalculator.vue'
import './style.css'
import { Theme } from 'vitepress' // 确保导入 Theme 类型

export default {
  ...DefaultTheme,
  enhanceApp({ app }) {
    // 注册全局组件
    app.component('HashCalculator', HashCalculator)

  }
} satisfies Theme
