#include "mywc.h"

// 创建哈希表
WordCount **wc_create_hash_table() {
  WordCount **hash_table = calloc(HASH_SIZE, sizeof(WordCount *));
  return hash_table;
}

// 简单的哈希函数
unsigned int hash(const char *word) {
  unsigned long hash = 5381;
  int c;
  while ((c = *word++))
    hash = ((hash << 5) + hash) + c; // hash * 33 + c
  return hash % HASH_SIZE;
}

// 检查字符是否构成单词的一部分
bool is_valid_word_char(char c) { return isalpha(c) || c == '\''; }

char to_lower(char c) {
  return (char)tolower((unsigned char)c);
}

static int compare_word_counts(const void *a, const void *b) {
  const WordCount *wa = *(WordCount * const *)a;
  const WordCount *wb = *(WordCount * const *)b;
  if (wa->count != wb->count) {
    return wb->count - wa->count;
  }
  return strcmp(wa->word, wb->word);
}

// 添加单词到哈希表
void add_word(WordCount **hash_table, const char *word) {
  unsigned int index = hash(word);
  WordCount *entry = hash_table[index];

  while (entry != NULL) {
    if (strcmp(entry->word, word) == 0) {
      entry->count++;
      return;
    }
    entry = entry->next;
  }

  entry = malloc(sizeof(WordCount));
  if (entry == NULL) {
    return;
  }
  strncpy(entry->word, word, MAX_WORD_LEN - 1);
  entry->word[MAX_WORD_LEN - 1] = '\0';
  entry->count = 1;
  entry->next = hash_table[index];
  hash_table[index] = entry;
}

// 打印单词统计结果
void print_word_counts(WordCount **hash_table) {
  printf("Word Count Statistics:\n");
  printf("======================\n");

  int total = 0;
  for (int i = 0; i < HASH_SIZE; i++) {
    for (WordCount *entry = hash_table[i]; entry != NULL; entry = entry->next) {
      total++;
    }
  }

  WordCount **nodes = malloc((size_t)total * sizeof(WordCount *));
  if (nodes == NULL) {
    return;
  }

  int idx = 0;
  for (int i = 0; i < HASH_SIZE; i++) {
    for (WordCount *entry = hash_table[i]; entry != NULL; entry = entry->next) {
      nodes[idx++] = entry;
    }
  }

  qsort(nodes, (size_t)total, sizeof(WordCount *), compare_word_counts);
  for (int i = 0; i < total; i++) {
    printf("%-20s %d\n", nodes[i]->word, nodes[i]->count);
  }

  free(nodes);
}

// 释放哈希表内存
void wc_free_hash_table(WordCount **hash_table) {
  if (hash_table == NULL) {
    return;
  }
  for (int i = 0; i < HASH_SIZE; i++) {
    WordCount *entry = hash_table[i];
    while (entry != NULL) {
      WordCount *temp = entry;
      entry = entry->next;
      free(temp);
    }
  }
  free(hash_table);
}

// 处理文件并统计单词
void process_file(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  WordCount **hash_table = wc_create_hash_table();
  char word[MAX_WORD_LEN];
  int word_pos = 0;
  int c;

  while ((c = fgetc(file)) != EOF) {
    if (is_valid_word_char(c)) {
      if (word_pos < MAX_WORD_LEN - 1) {
        word[word_pos++] = to_lower(c);
      }
    } else {
      if (word_pos > 0) {
        word[word_pos] = '\0';
        add_word(hash_table, word);
        word_pos = 0;
      }
    }
  }

  // 处理文件末尾的最后一个单词
  if (word_pos > 0) {
    word[word_pos] = '\0';
    add_word(hash_table, word);
  }

  fclose(file);
  print_word_counts(hash_table);
  wc_free_hash_table(hash_table);
}

int __cmd_mywc(const char* filename) {
  process_file(filename);
  return 0;
}
