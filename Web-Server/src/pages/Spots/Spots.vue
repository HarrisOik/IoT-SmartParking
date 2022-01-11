<template>
  <Header />
  <Content />
  <Footer />
</template>
<script>
import Content from "./components/Content.vue";
import Header from "../../components/Header.vue";
import Footer from "../../components/Footer.vue";

export default {
  name: "Spots",
  components: {
    Content,
    Header,
    Footer,
  },
};
</script>
