import { h } from 'vue'
import DefaultTheme from 'vitepress/theme'
import HashCalculator from './components/HashCalculator.vue'
import { onMounted, watch, nextTick } from 'vue'
import { useRoute, useData } from 'vitepress'
import type { Theme } from 'vitepress'
import NotFound from './NotFound.vue'
import 'viewerjs/dist/viewer.min.css';
import imageViewer from 'vitepress-plugin-image-viewer';
import vImageViewer from 'vitepress-plugin-image-viewer/lib/vImageViewer.vue';
import './style/index.css'

export default {
  ...DefaultTheme,
  
  Layout() {
    const { frontmatter } = useData()
    const props: Record<string, any> = {}

    if (frontmatter.value?.layoutClass) {
      props.class = frontmatter.value.layoutClass
    }

    return h(DefaultTheme.Layout, props, {
      'not-found': () => h(NotFound)
    })
  },

  setup() {
        const route = useRoute();
        imageViewer(route);    
  },

  enhanceApp({ app }) {
    app.component('HashCalculator', HashCalculator)
  }
} satisfies Theme