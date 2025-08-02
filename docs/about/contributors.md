---
layout: page
title: 贡献者
sidebar: false
hidesidebar: true
---

<!-- markdownlint-disable MD033 MD041 -->
<script setup>
import {
  VPTeamPage,
  VPTeamPageTitle,
  VPTeamMembers
} from 'vitepress/theme'
// 定义成员信息
const members = [
  {
    avatar: "/head/Young-Lord.jpg",
    name: "Young Lord",
    title: "开发者",
    desc: "THE END IS NEVER THE END",
    links: [
      { icon: 'github', link: "https://github.com/Young-Lord" }
    ]
  },
  {
    avatar: "/head/Ljzd-PRO.jpg",
    name: "Ljzd PRO",
    title: "开发者",
    desc: "暂无个人简介",
    links: [
      { icon: 'github', link: "https://github.com/Ljzd-PRO" }
    ]
  },
  {
    avatar: "/head/shenjackyuanjie.jpg",
    name: "Shen Jack",
    title: "开发者",
    desc: "happy lazy | HWS with me",
    links: [
      { icon: 'github', link: "https://github.com/shenjackyuanjie" }
    ]
  },
  {
    avatar: "/head/leng-yue.jpg",
    name: "Leng Yue",
    title: "开发者",
    desc: "Push the boundary of artificial general intelligence.",
    links: [
      { icon: 'github', link: "https://github.com/leng-yue" }
    ]
  },
  {
    avatar: "/head/fumiama.jpg",
    name: "Fumiama",
    title: "开发者",
    desc: "千载何方归梦，棹舟星河波开。",
    links: [
      { icon: 'github', link: "https://github.com/fumiama" }
    ]
  },
  {
    avatar: "/head/alphagocc.jpg",
    name: "Alpha Gocc",
    title: "开发者",
    desc: "Alphagocc",
    links: [
      { icon: 'github', link: "https://github.com/alphagocc" }
    ]
  },
  {
    avatar: "/head/Mythologyli.jpg",
    name: "Mythology Li",
    title: "开发者",
    desc: "Embedded Systems, Robotics, Graphing Calculators and Minecraft!",
    links: [
      { icon: 'github', link: "https://github.com/Mythologyli" }
    ]
  },
  {
    avatar: "/head/yllhwa.jpg",
    name: "Yllhwa",
    title: "开发者",
    desc: "暂无个人简介",
    links: [
      { icon: 'github', link: "https://github.com/yllhwa" }
    ]
  },
  {
    avatar: "/head/siten.jpg",
    name: "Siten",
    title: "开发者",
    desc: "暂无个人简介",
    links: [
      { icon: 'github', link: "https://github.com/siten" }
    ]
  }
]


const contributors = [
  {
    avatar: "https://ooo.0x0.ooo/2024/10/07/O4wGIc.jpg",
    name: "Raincarnator",
    title: "贡献者",
    desc: '提交了 <a href="https://github.com/QQBackup/QQDecrypt/pull/1#issue-2568844396" target="_blank">PR #1</a>: docs: add more information',
    links: [
      { icon: 'github', link: "https://github.com/Raincarnator" }
    ]
  },

  {
    avatar: "https://ooo.0x0.ooo/2024/11/16/OHL7jx.png",
    name: "Wenz-jam",
    title: "贡献者",
    desc: '提交了 <a href="https://github.com/QQBackup/qq-win-db-key/pull/46" target="_blank">PR #46</a>:添加一种linux下获取密钥的方式',
    links: [
      { icon: 'github', link: "https://github.com/Wenz-jam" }
    ]
  },

  {
    avatar: "https://ooo.0x0.ooo/2025/01/04/OEHG9B.jpg",
    name: "Dao1023",
    title: "贡献者",
    desc: '<a href="https://github.com/QQBackup/qq-win-db-key/issues/50" target="_blank">issues #50</a>:补充NTQQ(Windows)教程',
    links: [
      { icon: 'github', link: "https://github.com/Dao1023" }
    ]
  },  

  {
    avatar: "/head/Disa.png",
    name: "Disa Tale",
    title: "贡献者",
    desc: '帮助修正 pcqq_rekey_to_none.cpp 中代码错误，并提供编译版本',
    links: [
      { icon: 'github', link: "https://github.com/DisaWdcba" }
    ]
  },  

  {
    avatar: "https://ooo.0x0.ooo/2025/08/02/Of5O7S.png",
    name: "miniyu157",
    title: "贡献者",
    desc: '<a href="https://github.com/QQBackup/QQDecrypt/issues/3" target="_blank">issues #3</a>:投稿社区项目<a href="https://github.com/miniyu157/QQRootFastDecrypt" target="_blank">QQRootFastDecrypt</a>',
    links: [
      { icon: 'github', link: "https://github.com/miniyu157" }
    ]
  },  

  {
    avatar: "https://ooo.0x0.ooo/2025/08/02/Of5aLN.png",
    name: "C6H5FJokey",
    title: "贡献者",
    desc: '<a href="https://github.com/QQBackup/QQDecrypt/issues/4" target="_blank">issues #4</a>:帮助指出文档错误',
    links: [
      { icon: 'github', link: "https://github.com/C6H5FJokey" }
    ]
  },  

]
</script>

<VPTeamPage>

  <VPTeamPageTitle>
    <template #title>
      仓库成员
    </template>
    <template #lead>
      若需要修改/增删信息可在仓库发起 PR 或issues
    </template>
  </VPTeamPageTitle>

  <VPTeamMembers :members="members" />

  <VPTeamPageTitle>
    <template #title>
       仓库贡献者
    </template>
    <template #lead>
      这些成员为项目做出了贡献
    </template>
  </VPTeamPageTitle>

  <VPTeamMembers :members="contributors" />
</VPTeamPage>